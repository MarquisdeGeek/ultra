#include "../types.hpp"
#include "../config.hpp"
#include "../request.hpp"
#include "../response_text.hpp"
#include "base.hpp"


bool
UltraRemap::evaluate(sgxString &result, const UltraLine *pLine, const UltraRequest *pRequest) const {
	bool rt = true;

	// Start with ourselves, in a depth-first scan
	sgxString childrenString(pLine->m_szLine);

	// Then process all the children nodes
	std::vector<UltraLine *>::const_iterator cit = pLine->m_Children.begin();
	for(;cit != pLine->m_Children.end();++cit) {
		(*cit)->m_pRemap->evaluate(childrenString, *cit, pRequest);
	}

	// Then remap the completed string, if appropriate
	if (pLine->m_bIsMeta) {
		sgxString r1;
		sgxString r2;

		pRequest->m_pConfig->getRemapString(r1, childrenString);
		pRequest->getRemapString(r2, r1);

		result += r2;

	} else {
		result += childrenString;
	}

	return rt;

}
