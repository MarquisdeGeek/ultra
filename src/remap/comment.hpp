#ifndef ULTRA_REMAP_COMMENT

#define ULTRA_REMAP_COMMENT		1

class UltraRemapComment : public UltraRemap {
public:
	virtual void		process(sgxString &resultPattern, const sgxString &source) const;
};

#endif
