#include "ultra.hpp"
#include "output/base.hpp"
#include "remap/base.hpp"

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
		m_pContentRoot->preprocess(pConfig);
		delete []pData;
	}
}

UltraResponseText::~UltraResponseText() {
	delete m_pContentRoot;
	m_pContentRoot = NULL;
}

void
UltraLine::preprocess(const UltraConfig *pConfig) {
	if (m_bIsMeta) {
		m_pRemap = pConfig->getRemap(m_szLine);
	}

	if (!m_pRemap) {
		m_pRemap = pConfig->getNullRemap();
	}

	// Then process all the children nodes
	std::vector<UltraLine *>::const_iterator cit = m_Children.begin();
	for(;cit != m_Children.end();++cit) {
		(*cit)->preprocess(pConfig);
	}
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
	return pOutput->write(r.c_str());
}


//
// The individual lines of the page, split at the delimiters {( and )} by default
//
UltraLine::UltraLine(UltraLine *pParent) {
	m_pParent = pParent;
	m_bIsMeta = false;
	m_pRemap = NULL;

	if (pParent) {
		pParent->addChild(this);
	}
}

UltraLine::~UltraLine() {
	//NOP
}

void
UltraLine::addChild(UltraLine *pChild) {
	m_Children.push_back(pChild);
}

bool
UltraLine::process(sgxString &result, const UltraConfig *pConfig, const UltraRequest *pRequest) const {
	return m_pRemap->evaluate(result, this, pRequest);
}

