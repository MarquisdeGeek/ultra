#ifndef ULTRA_REMAP_STATS

#define ULTRA_REMAP_STATS		1

#include "dumpdb.hpp"

class UltraDB;

class UltraRemapStats : public UltraRemapDumpDB {
public:
	UltraRemapStats(const UltraDB *pDB);
};


#endif
