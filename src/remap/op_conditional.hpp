#ifndef ULTRA_REMAP_OP_CONDITIONAL

#define ULTRA_REMAP_OP_CONDITIONAL		1

#include "../types.hpp"

class UltraLine;
class UltraConfigBase;
class UltraRequest;

class UltraRemapOpConditional : public UltraRemap {
public:

	virtual void		process(sgxString &resultPattern, const sgxString &source) const;
	virtual bool 		evaluate(sgxString &result, const UltraLine *pLine, const UltraRequest *pRequest) const;
};

#endif
