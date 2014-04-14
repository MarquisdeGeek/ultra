#include "../database.hpp"
#include "../database.hpp"
#include "base.hpp"
#include "database_delete.hpp"


UltraRemapDatabaseDelete::UltraRemapDatabaseDelete(UltraDB *pData) {
	m_pData = pData;
}

void
UltraRemapDatabaseDelete::process(sgxString &resultPattern, const sgxString &source) const {
	m_pData->deleteNode(source);
}
