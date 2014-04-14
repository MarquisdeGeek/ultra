#include "../service.hpp"

#include "base.hpp"
#include "serialize.hpp"


class Service;

UltraRemapSerializeData::UltraRemapSerializeData(Service *pService) {
	m_pService = pService;
}

void
UltraRemapSerializeData::process(sgxString &resultPattern, const sgxString &source) const {
	if (m_pService->serialize()) {
		resultPattern = "Data saved: OK";
	} else {
		resultPattern = "ERROR: Could not serialize DB.";
	}
}
