#ifndef ULTRA_REMAP_OP_EQUAL

#define ULTRA_REMAP_OP_EQUAL		1

#include "../types.hpp"


class UltraRemapOpEqual : public UltraRemap {
public:
	virtual ~UltraRemapOpEqual(){}

	virtual void		process(sgxString &resultPattern, const sgxString &source) const;
};

#endif
