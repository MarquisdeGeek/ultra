#ifndef ULTRA_REMAP_REDIRECTION

#define ULTRA_REMAP_REDIRECTION		1


class UltraRemapRedirection : public UltraRemap {
public:
	virtual void		process(sgxString &resultPattern, const sgxString &source) const;
};

#endif
