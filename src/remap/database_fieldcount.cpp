#include "../database.hpp"
#include "../utils.hpp"

#include "base.hpp"
#include "database_fieldcount.hpp"


UltraRemapDatabaseFieldCount::UltraRemapDatabaseFieldCount(UltraDB *pData) {
	m_pData = pData;
}

 void
UltraRemapDatabaseFieldCount::process(sgxString &resultPattern, const sgxString &source) const {
	int count = m_pData->getChildCount(source);
	intToString(resultPattern, count);
}
