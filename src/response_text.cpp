#include "ultra.hpp"
#include "output/base.hpp"

#include "config.hpp"
#include "response.hpp"
#include "response_text.hpp"

#include "service.hpp"
#include "utils.hpp"

#include "request.hpp"


UltraResponseText::UltraResponseText(const UltraConfig *pConfig, const sgxString &filename) :  UltraResponse(pConfig, filename)  {

	m_pContentRoot = new UltraLine(NULL);

	size_t length;
	unsigned char *pData = ::slurp(filename, length, 1);
	if (pData) {
		pData[length] = '\0';
		parse(m_pContentRoot, NULL, pData);
		delete []pData;
	}
}

UltraResponseText::~UltraResponseText() {
	//NOP
}

/*
 * Split the content string according the meta variables on load,
 * then build the page by streaming each node out.
 */
unsigned char *
UltraResponseText::parse(UltraLine *pParent, UltraLine *pCurrentNode, unsigned char *pData) {

	while(*pData) {
		if (!pCurrentNode) {
			pCurrentNode = new UltraLine(pParent);
		}

		if (*pData == ULTRA_META_OPEN1 && *(pData+1) == ULTRA_META_OPEN2) {
			// NOTE: This is slightly inefficient since it creates an empty node for
			// each nested {meta} tag
			UltraLine *pChild = new UltraLine(pCurrentNode);
			pChild->m_bIsMeta = true;

			pData = parse(pCurrentNode, pChild, pData+2);

			// Once the recusive 'parse' returns, we continue add features as siblings.
			pParent = pCurrentNode;

			// Setting pCurrentNode to NULL causes a new node to be created on the next iteration.
			pCurrentNode = NULL;


		} else if (*pData == ULTRA_META_CLOSE1 && *(pData+1) == ULTRA_META_CLOSE2) {
			return pData + 2;

		} else {
			pCurrentNode->m_szLine += *pData++;
		}

	}

	return pData;
}

bool
UltraResponseText::writeBody(UOutput *pOutput, const UltraRequest *pRequest) const {

	sgxString r;
	m_pContentRoot->process(r, m_pConfig, pRequest);
	pOutput->write(r.c_str());

	return true;
}


//
// The individual lines of the page, split at the delimiters {( and )} by default
//
UltraLine::UltraLine(UltraLine *pParent) {
	m_pParent = pParent;
	m_bIsMeta = false;

	if (pParent) {
		pParent->addChild(this);
	}
}

void
UltraLine::addChild(UltraLine *pChild) {
	m_Children.push_back(pChild);
}


bool
UltraLine::process(sgxString &result, const UltraConfig *pConfig, const UltraRequest *pRequest) const {

	// Start with ourselves, in a depth-first scan
	sgxString childrenString(m_szLine);

	// Then process all the children nodes
	std::vector<UltraLine *>::const_iterator cit = m_Children.begin();
	for(;cit != m_Children.end();++cit) {
		(*cit)->process(childrenString, pConfig, pRequest);
	}

	// Then remap the completed string, if appropriate
	if (m_bIsMeta) {
		sgxString r1;
		sgxString r2;

		pConfig->getRemapString(r1, childrenString);
		pRequest->getRemapString(r2, r1);

		result += r2;

	} else {
		result += childrenString;
	}

	return true;
}

