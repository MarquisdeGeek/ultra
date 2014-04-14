#ifndef ULTRA_RESPONSE

#define ULTRA_RESPONSE	1

#include "types.hpp"


class UltraRequest;
class UltraConfig;
class UOutput;


class UltraResponse {
public:
	UltraResponse(const UltraConfig *pConfig, const sgxString &filename);

	virtual ~UltraResponse();
	virtual bool	writeHeader(UOutput *pOutput);
	virtual bool	writeBody(UOutput *pOutput, const UltraRequest *pRequest = NULL) const = 0;

protected:
	const UltraConfig *	m_pConfig;

private:
	sgxString			m_ContentType;

};

#endif
