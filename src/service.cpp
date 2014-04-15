#include <string.h>
#include <stdio.h>

#include "version.hpp"
#include "ultra.hpp"
#include "output/base.hpp"

#include "database.hpp"
#include "service.hpp"
#include "fileset.hpp"
#include "request.hpp"
#include "response.hpp"

#include "remap/remap.hpp"


Service *
Service::build(const UltraConfigSettings *pConfig) {
	Service *pService = new Service(pConfig);

	// Process pages with defined constants {const:xxx} and common {home}
	pService->processPages();

	return pService;
}

Service::Service(const UltraConfigSettings *pConfig)
	: m_pConfigSettings(pConfig) {

	m_pData = new UltraDB();
	m_pConfig = new UltraConfig(pConfig, m_pData);

	// Get the whole list of files into memory
	m_pPages = new UltraFileSet(m_pConfig);
	m_pPages->loadFiles(m_pConfig);

	// Iterate all files and if they live in the db/ folder then load them as if they were separate tables
	PageMap::iterator it = m_pPages->m_DBList.begin();
	sgxString dbStub(pConfig->m_RootPath + "/db/");
	for(;it != m_pPages->m_DBList.end();++it) {
		m_pData->import(it->first);
	}

	// Add custom meta vars
	m_pConfig->addRemap("sys:flush", new UltraRemapSerializeData(this));

	// Add DB fields
	m_pConfig->addRemapWildcard("db!:", new UltraRemapDatabaseFields(m_pData, true));
	m_pConfig->addRemapWildcard("db:", new UltraRemapDatabaseFields(m_pData, false));
	m_pConfig->addRemapWildcard("db.count:", new UltraRemapDatabaseFieldCount(m_pData));
	m_pConfig->addRemapWildcard("db.delete:", new UltraRemapDatabaseDelete(m_pData));

}

Service::~Service() {
	delete m_pPages;
	delete m_pData;
	delete m_pConfig;
}

Service *
Service::replicate() {
	return Service::build(this->m_pConfigSettings);
}

bool
Service::serialize() {
	bool rt = true;

	// Write all data to the root (for debug only)
#if ULTRA_DEBUG==1
	sgxString dbFileName = m_pConfigSettings->m_RootPath + "/all.db";
	rt &= m_pData->serializeAll(dbFileName);
#endif

	sgxString dbDirName = m_pConfigSettings->m_RootPath + "/db/";
	rt &= m_pData->serializeAllTables(dbDirName);

	return rt;
}

void
Service::processPages() {
	m_pPages->preProcessPages();
}

void
Service::writeHeader(UOutput *pOutput, const int code) {
	char header[200];
	sprintf(header, "HTTP/1.0 %d OK%s", code, ULTRA_EOL);
	pOutput->write(header, strlen(header));

	pOutput->write("Server: ");
	pOutput->write(ULTRA_VERSION);
	pOutput->write(ULTRA_EOL);
}


void
Service::buildPage(UOutput *pOutput, const char *buffer) {
#if UBUILD_SUPPORT_EXCEPTIONS==1
	try {
#endif

	// TODO: Move UltraRequest into a DB so {db:request:url} can be used
	// Also, {db:request.get.param}, also put? plus :client.ip :client.ua etc
	// TODO: Mark some DBs as 'internal' to stop serialize writing them out to user space
	// TODO: Improve, so the request object's not reconstructed each time
	UltraRequest request(buffer);
	request.addRemapWildcard("get:", new UltraRemapGetArguments(request));
	request.addRemapWildcard("ssi:", new UltraRemapServerSideIncludes(this, &request));


	// TODO: validate url against .. %20 and other such things
	// This assumes a well-formed URL, beginning with a slash.
	// Duplicate slashes means the map lookup fails. FIXME
	sgxString url(m_pConfigSettings->m_RootPath);
	url += "/docs" + request.m_URL;
	UltraResponse *pFileToServe = m_pPages->m_PageList[url];


	if (pFileToServe) {
		log(LOG_INFO, "GET %s", url.c_str());

		writeHeader(pOutput, 200);
		pFileToServe->writeHeader(pOutput);
		pOutput->write(ULTRA_EOL);

		pFileToServe->writeBody(pOutput, &request);

#if UBUILD_SUPPORT_ACCESS_STATS==1
		m_pConfig->m_pAccessStats->incInteger("requests.access.url." + url, 1);
		m_pConfig->m_pAccessStats->incInteger("requests.access.count", 1);
#endif

	} else {
		log(LOG_INFO, "404 %s", url.c_str());
		writeHeader(pOutput, 404);
		pOutput->write("404");

#if UBUILD_SUPPORT_ACCESS_STATS==1
		m_pConfig->m_pAccessStats->incInteger("requests.missing.url." + url, 1);
		m_pConfig->m_pAccessStats->incInteger("requests.missing.count", 1);
#endif
	}

#if UBUILD_SUPPORT_EXCEPTIONS==1
	} catch (...) {
		log(LOG_ERROR, "Exception in Service::buildPage");
	}
#endif
}


