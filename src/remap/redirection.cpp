#include "base.hpp"
#include "redirection.hpp"


void
UltraRemapRedirection::process(sgxString &resultPattern, const sgxString &source) const {
	resultPattern = "<meta http-equiv='refresh' content='0;url=" + source + "'>";
}
