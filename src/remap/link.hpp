#ifndef ULTRA_REMAP_LINK

#define ULTRA_REMAP_LINK		1


class UltraRemapLink : public UltraRemap {
public:
	virtual void		process(sgxString &resultPattern, const sgxString &source) const;
};

#endif
