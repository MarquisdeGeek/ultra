#include "ultra.hpp"
#include "output/base.hpp"

#include "config.hpp"
#include "response.hpp"


UltraResponse::UltraResponse(const UltraConfig *pConfig, const sgxString &filename) : m_pConfig(pConfig) {
	m_ContentType = "Content-type: ";
	pConfig->getContentType(m_ContentType, filename);
	m_ContentType += ULTRA_EOL;
}

UltraResponse::~UltraResponse() {
	m_pConfig = NULL;
}

bool
UltraResponse::writeHeader(UOutput *pOutput) {
	return pOutput->write(m_ContentType.c_str());

}

