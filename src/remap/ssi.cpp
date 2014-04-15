#include "../config.hpp"
#include "../service.hpp"
#include "../response_text.hpp"
#include "../fileset.hpp"
#include "../request.hpp"

#include "base.hpp"
#include "ssi.hpp"



UltraRemapServerSideIncludes::UltraRemapServerSideIncludes(Service *pService, UltraRequest * pRequest) {
	m_pService = pService;
	m_pRequest = pRequest;
}

void
UltraRemapServerSideIncludes::process(sgxString &resultPattern, const sgxString &source) const {
	sgxString ssi;

	m_pService->m_pConfig->getRootPath(ssi);
	ssi += "/docs/ssi/" + source;

	UltraResponseText *pFileToInclude = (UltraResponseText *)m_pService->m_pPages->m_PageList[ssi];

	if (pFileToInclude) {
		pFileToInclude->m_pContentRoot->process(resultPattern, m_pService->m_pConfig, m_pRequest);
	} else {
		resultPattern = "<!-- Unknown SSI -->";
	}
}
