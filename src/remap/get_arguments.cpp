#include "../request.hpp"

#include "base.hpp"
#include "get_arguments.hpp"


UltraRemapGetArguments::UltraRemapGetArguments(const UltraRequest &request) : m_Request(request) {
}

void
UltraRemapGetArguments::process(sgxString &resultPattern, const sgxString &source) const {
	m_Request.getString(source, resultPattern);
}
