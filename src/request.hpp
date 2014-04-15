#ifndef ULTRA_REQUEST

#define ULTRA_REQUEST		1

#include "types.hpp"
#include "config.hpp"

class UltraRequest : public UltraConfigBase {
public:
	UltraRequest(const sgxString &req, const UltraConfig *pConfig = NULL);
	virtual ~UltraRequest();

	virtual bool getString(const sgxString &name, sgxString &value) const;

public:
	sgxString 			m_Verb;
	sgxString 			m_URL;
	const UltraConfig *	m_pConfig;
};

#endif
