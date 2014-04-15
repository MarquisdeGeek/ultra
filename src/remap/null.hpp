#ifndef ULTRA_REMAP_NULL

#define ULTRA_REMAP_NULL		1


class UltraRemapNull : public UltraRemap {
public:
	virtual void		process(sgxString &resultPattern, const sgxString &source) const;
};

#endif
