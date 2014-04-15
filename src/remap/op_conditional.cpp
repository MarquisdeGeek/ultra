#include "../types.hpp"
#include "../ultra.hpp"
#include "../config.hpp"
#include "../request.hpp"
#include "../response_text.hpp"
#include "../utils.hpp"

#include "base.hpp"
#include "op_conditional.hpp"

void
UltraRemapOpConditional::process(sgxString &resultPattern, const sgxString &source) const {
	// NOP - all processing is done in the evaluator
}

bool
UltraRemapOpConditional::evaluate(sgxString &result, const UltraLine *pLine, const UltraRequest *pRequest) const {
	bool rt = true;

	// Strip the op.==: bit
	size_t colonPosition = pLine->m_szLine.find_first_of(':');
	sgxString childrenString(pLine->m_szLine.substr(colonPosition + 1));


	// Then process all the children nodes
	std::vector<UltraLine *>::const_iterator cit = pLine->m_Children.begin();
	for(;cit != pLine->m_Children.end();++cit) {
		rt &= (*cit)->m_pRemap->evaluate(childrenString, *cit, pRequest);
	}

	// Then remap the completed string, if appropriate

	std::vector<sgxString> argList;
	int numArgs = ::splitString(argList, childrenString, ' ');

	switch(numArgs) {
	case	2:	// if-then
		if (argList[0] == "1") {
			result += argList[1];
		}
		break;
	case	3:	// if-then-else
		if (argList[0] == "1") {
			result += argList[1];
		} else {
			result += argList[2];
		}
		break;
	default:
		log(LOG_WARNING, "Only %d arguments in a conditional", numArgs);
	}


	return rt;

}
