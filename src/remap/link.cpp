#include "base.hpp"
#include "link.hpp"

void		
UltraRemapLink::process(sgxString &resultPattern, const sgxString &source) const {
	size_t spaceAt = source.find(' ');
	if (spaceAt != sgxString::npos) {
		sgxString url = source.substr(0, spaceAt);
		sgxString anchor = source.substr(spaceAt+1);

		resultPattern = "<a href=\"" + url + "\">" + anchor + "</a>";
	} else {
		resultPattern = "<a href=\"" + source + "\">" + source + "</a>";
	}
}

