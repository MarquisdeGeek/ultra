#ifndef ULTRA_REMAP_OP_LIMIT

#define ULTRA_REMAP_OP_LIMIT		1


class UltraRemapOpLimit : public UltraRemap {
public:
	virtual void		process(sgxString &resultPattern, const sgxString &source) const;
};

#endif
