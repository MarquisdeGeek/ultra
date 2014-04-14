#include <stdlib.h>

#include "../ultra.hpp"
#include "../utils.hpp"

#include "base.hpp"
#include "op_limit.hpp"


void	
UltraRemapOpLimit::process(sgxString &resultPattern, const sgxString &source) const {
	std::vector<sgxString> result;

	int argCount = splitString(result, source, ' ');

	if (argCount >= 3) {
		int v = atoi(result[0].c_str());
		int minimum = atoi(result[1].c_str());
		int maximum = atoi(result[2].c_str());

		if (v < minimum) {
			v = minimum;
		} else if (v > maximum) {
			v = maximum;
		}

		intToString(resultPattern, v);

	} else {
		log(LOG_WARNING, "op.limit didn't have 3 args");
	}

}
