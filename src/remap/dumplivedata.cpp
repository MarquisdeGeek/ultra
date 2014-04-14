#include "base.hpp"
#include "dumpdb.hpp"
#include "dumplivedata.hpp"

#include "../database.hpp"


UltraRemapDumpLiveData::UltraRemapDumpLiveData(UltraDB *pDatabase) : UltraRemapDumpDB(NULL) {
	m_pDatabase = pDatabase;
}

void		
UltraRemapDumpLiveData::process(sgxString &resultPattern, const sgxString &source) const {
	m_pDatabase->dumpTables(resultPattern, "<br>");
}
