#ifndef ULTRA_RESPONSE_BINARY

#define ULTRA_RESPONSE_BINARY	1

#include "types.hpp"

class UltraConfigBase;
class UltraConfig;
class UltraRequest;
class UOutput;
class UltraResponse;


class UltraResponseBinary : public UltraResponse {
public:
	UltraResponseBinary(const UltraConfig *pConfig, const sgxString &filename);
	virtual ~UltraResponseBinary();

	virtual bool	writeHeader(UOutput *pOutput);
	virtual bool	writeBody(UOutput *pOutput, const UltraRequest *pRequest = NULL) const;

private:
	size_t				m_BinaryLength;
	unsigned char *		m_pBinaryData;
};


#endif
