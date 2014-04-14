#ifndef ULTRA_REMAP_EXECUTE

#define ULTRA_REMAP_EXECUTE		1


class UltraRemapExecute : public UltraRemap {
public:
	virtual void		process(sgxString &resultPattern, const sgxString &source) const;

};

#endif
