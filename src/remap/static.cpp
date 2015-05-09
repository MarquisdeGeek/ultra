#include "base.hpp"
#include "static.hpp"


UltraRemapStatic::UltraRemapStatic(sgxString &target) :
	m_Result(target) {
}

UltraRemapStatic::UltraRemapStatic(const char *pTarget) :
	m_Result(pTarget) {
}

void	
UltraRemapStatic::process(sgxString &resultPattern, const sgxString &source) const {
	resultPattern = m_Result;
}
