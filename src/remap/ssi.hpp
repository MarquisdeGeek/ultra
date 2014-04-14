#ifndef ULTRA_REMAP_SSI

#define ULTRA_REMAP_SSI		1


class UltraRemapServerSideIncludes : public UltraRemap {
public:
	UltraRemapServerSideIncludes(Service *pService, UltraRequest * pRequest);

	virtual void		process(sgxString &resultPattern, const sgxString &source) const;

private:
	Service * 		m_pService;
	UltraRequest * 	m_pRequest;
};

#endif
