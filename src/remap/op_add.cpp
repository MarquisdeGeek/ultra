#include <stdlib.h>

#include "../ultra.hpp"
#include "../utils.hpp"

#include "base.hpp"
#include "op_add.hpp"


void
UltraRemapOpAdd::process(sgxString &resultPattern, const sgxString &source) const {
	std::vector<sgxString> result;

	int total = 0;
	int argCount = splitString(result, source, ' ');
	for(int i=0;i<argCount;++i) {
		total += atoi(result[i].c_str());
	}
	intToString(resultPattern, total);
}

