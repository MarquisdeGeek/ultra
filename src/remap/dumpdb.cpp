#include "base.hpp"
#include "dumpdb.hpp"

#include "../ultra.hpp"
#include "../database.hpp"


UltraRemapDumpDB::UltraRemapDumpDB(const UltraDB *pDB) {
	m_pDatabase = pDB;
}

void
UltraRemapDumpDB::process(sgxString &resultPattern, const sgxString &source) const {
	m_pDatabase->dumpTables(resultPattern, "<br>");
}
