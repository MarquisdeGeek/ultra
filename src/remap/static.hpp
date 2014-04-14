#ifndef ULTRA_REMAP_STATIC

#define ULTRA_REMAP_STATIC		1


class UltraRemapStatic : public UltraRemap {
public:
	UltraRemapStatic(sgxString &target);
	UltraRemapStatic(const char *pTarget);

	virtual void		process(sgxString &resultPattern, const sgxString &source) const;
	
private:
	sgxString m_Result;
};

#endif
