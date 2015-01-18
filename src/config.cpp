#include "ultra.hpp"
#include "database.hpp"

#include "remap/remap.hpp"

#include "config.hpp"
#include "request.hpp"

UltraConfig::UltraConfig(const UltraConfigSettings *pConfigSettings, UltraDB *pDatabase) : UltraConfigBase(),
	m_Mode(pConfigSettings->m_Configuration), m_RootPath(pConfigSettings->m_RootPath) {

	// Store back pointer to the database, should we need it
	m_pDatabase = pDatabase;

	// Load the config file
	sgxString configFile = pConfigSettings->m_RootPath + "/config/ultra.conf";

	// This is ctor'd in the base
	m_pConfigData->import(configFile);

	sgxString mime = pConfigSettings->m_RootPath + "/config/mime.conf";
	m_pMIMETypes = new UltraDB();
	m_pMIMETypes->import(mime);


	m_pAccessStats = new UltraDB();


	addRemap("home", new UltraRemapStatic("<a href='/'>Home</a>"));

	addRemapWildcard("link:", 		new UltraRemapLink());
	addRemapWildcard("redirect:", 	new UltraRemapRedirection());
	addRemapWildcard("exec:", 		new UltraRemapExecute());
	addRemapWildcard("config.dump:",new UltraRemapDumpDB(m_pConfigData));
	addRemapWildcard("mime.dump:",	new UltraRemapDumpDB(m_pMIMETypes));
	addRemapWildcard("db.dump:",	new UltraRemapDumpLiveData(m_pDatabase));
	addRemapWildcard("stats.dump:", new UltraRemapStats(m_pAccessStats));
	addRemapWildcard("rem:",		new UltraRemapComment());

	addRemapWildcard("op.range:",	new UltraRemapOpLimit());
	addRemapWildcard("op.+:",		new UltraRemapOpAdd());
	addRemapWildcard("op.if:",		new UltraRemapOpConditional());
	addRemapWildcard("op.==:",		new UltraRemapOpEqual());

	// TODO: Load other mappings from config into here

	// Add dynamic mappings (e.g. time) into here
	addRemap("hours", 	new UltraRemapTime(0));
	addRemap("minutes", new UltraRemapTime(1));
	addRemap("seconds", new UltraRemapTime(2));
	addRemap("years", 	new UltraRemapTime(3));
	addRemap("month", 	new UltraRemapTime(4));
	addRemap("day", 	new UltraRemapTime(5));
	//

}

UltraConfig::~UltraConfig() {
	delete m_pAccessStats;
	delete m_pMIMETypes;
}

void
UltraConfig::getRootPath(sgxString &root) const {
	root = m_RootPath;
}


bool
UltraConfig::getString(const sgxString &name, sgxString &value) const {
	sgxString fullyQualifiedName;

	// We try each possible variation of name
	fullyQualifiedName = "config." + m_Mode + "." + name;
	if (m_pConfigData->getString(fullyQualifiedName, value)) {
		return true;
	}

	fullyQualifiedName = "config.default." + name;
	if (m_pConfigData->getString(fullyQualifiedName, value)) {
		return true;
	}

	fullyQualifiedName = "config." + name;
	if (m_pConfigData->getString(fullyQualifiedName, value)) {
		return true;
	}

	// And finally, just the name
	if (m_pConfigData->getString(name, value)) {
		return true;
	}
	return false;
}

bool
UltraConfig::getContentType(sgxString &type, const sgxString &filename) const {
	sgxString mime;
	size_t extensionPosition = filename.find_last_of('.');

	if (extensionPosition != sgxString::npos) {
		sgxString extension = filename.substr(extensionPosition + 1);

		if (m_pMIMETypes->getString(extension, mime)) {
			type += mime;
			return true;
		}
	}

	type += "text/html";
	return false;
}
