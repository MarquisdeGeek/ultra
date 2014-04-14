#ifndef ULTRA_REMAP_SERIALIZE

#define ULTRA_REMAP_SERIALIZE		1

class Service;

class UltraRemapSerializeData : public UltraRemap {
public:
	UltraRemapSerializeData(Service *pService);
	
	virtual void		process(sgxString &resultPattern, const sgxString &source) const;
	
private:
	Service *m_pService;
};


#endif
