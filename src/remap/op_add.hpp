#ifndef ULTRA_REMAP_OP_ADD

#define ULTRA_REMAP_OP_ADD		1


class UltraRemapOpAdd : public UltraRemap {
public:
	virtual void		process(sgxString &resultPattern, const sgxString &source) const;
};

#endif
