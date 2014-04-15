#include "ultra.hpp"
#include "output/base.hpp"

#include "config.hpp"

#include "request.hpp"
#include "response.hpp"
#include "response_binary.hpp"

#include "utils.hpp"


UltraResponseBinary::UltraResponseBinary(const UltraConfig *pConfig, const sgxString &filename) : UltraResponse(pConfig, filename) {
	m_pBinaryData = ::slurp(filename, m_BinaryLength, 0);
}

UltraResponseBinary::~UltraResponseBinary() {
	delete []m_pBinaryData;
	m_pBinaryData = NULL;
}

bool
UltraResponseBinary::writeHeader(UOutput *pOutput) {
	bool rt = UltraResponse::writeHeader(pOutput);

	sgxString size;
	intToString(size, m_BinaryLength);
	size = "Content-Length: " + size + ULTRA_EOL;

	return rt && pOutput->write(size.c_str());
}

bool
UltraResponseBinary::writeBody(UOutput *pOutput, const UltraRequest *pRequest/*UNUSED*/) const {
	if (m_pBinaryData) {
		return pOutput->write((const char *)m_pBinaryData, m_BinaryLength);
	}
	return true;
}




