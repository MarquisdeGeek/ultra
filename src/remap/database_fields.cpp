#include <stdlib.h>

#include "../database.hpp"

#include "base.hpp"
#include "database_fields.hpp"


UltraRemapDatabaseFields::UltraRemapDatabaseFields(UltraDB *pData, bool silent) {
	m_pData = pData;
	m_bSilent = silent;
}

 void
 UltraRemapDatabaseFields::process(sgxString &resultPattern, const sgxString &source) const {

	// If there's a symbol, it's an in-place process, such as an assignment or
	 // increment, affecting the DB entry directly.
	const char *pSymbols = "=+-?";
	const char *p = pSymbols;

	while(*p) {
		size_t symbolAt = source.find(*p);
		if (symbolAt != sgxString::npos) {
			sgxString dbEntry = source.substr(0, symbolAt);
			sgxString dbValue = source.substr(symbolAt+1);

			switch(*p) {
			case '?':
				if (dbValue != "") {
					m_pData->add(dbEntry, dbValue);
				}
				break;
			case '=':
				m_pData->add(dbEntry, dbValue);
				break;
			case '+':
				m_pData->incInteger(dbEntry, atoi(dbValue.c_str()));
				break;
			case '-':
				m_pData->incInteger(dbEntry, -atoi(dbValue.c_str()));
				break;
			}
			// All DB retrievals have the option of echo'ing the result, or not.
			// This is what silent is for.
			if (!m_bSilent) {
				m_pData->getString(dbEntry, resultPattern);
			}
			return;
		}
		//
		++p;
	}

	// No symbols, so just read the DB table
	if (!m_pData->getString(source, resultPattern) && !m_bSilent) {
		resultPattern = "<Unknown data>";
	}
}

