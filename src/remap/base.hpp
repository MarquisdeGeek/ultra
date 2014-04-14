#ifndef ULTRA_REMAP_BASE

#define ULTRA_REMAP_BASE		1

#include "../types.hpp"

class UltraRemap {
public:
	virtual ~UltraRemap(){}

	virtual void		process(sgxString &resultPattern, const sgxString &source) const = 0;
};

#endif
