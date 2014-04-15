#include "base.hpp"
#include "null.hpp"

void	
UltraRemapNull::process(sgxString &resultPattern, const sgxString &source) const {
	resultPattern = source;
}
