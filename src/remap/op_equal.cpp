#include "../types.hpp"
#include "../ultra.hpp"
#include "../config.hpp"
#include "../request.hpp"
#include "../response_text.hpp"
#include "../utils.hpp"

#include "base.hpp"
#include "op_equal.hpp"

void
UltraRemapOpEqual::process(sgxString &resultPattern, const sgxString &source) const {
	std::vector<sgxString> argList;
	int numArgs = ::splitString(argList, source, ' ');

	if (numArgs < 1) {
		log(LOG_WARNING, "You need at least 2 arguments to perform an op.==");
		return;
	}

	for(int i=1;i<numArgs;++i) {
		if (argList[0] != argList[i]) {
			resultPattern = "0";
			return;
		}
	}

	resultPattern = "1";
}

