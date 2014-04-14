#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <sstream>
#include <string>

#include "ultra.hpp"
#include "utils.hpp"


void
intToString(sgxString &result, const int value) {
	std::ostringstream c;
	c << value;
	result = c.str();
}

int
splitString(std::vector<sgxString> &result, const sgxString &source, const char delimiter) {
	result.clear();
	size_t firstAt = 0;
	size_t delimiterAt;
	while((delimiterAt = source.find(' ', firstAt)) != sgxString::npos) {
		sgxString item = source.substr(firstAt, delimiterAt - firstAt);
		result.push_back(item);
		firstAt = delimiterAt + 1;
	}

	// Any left?
	if (firstAt < source.length()) {
		sgxString item = source.substr(firstAt);
		result.push_back(item);
	}

	return result.size();
}

// 'padding' is a bad hack to allow the caller to slurp ASCII files
// by appending a NUL terminator to the data.
unsigned char *
slurp(const sgxString &filename, size_t &filesize, size_t padding) {

	FILE *fp = fopen(filename.c_str(), "rb");
	unsigned char *pData = NULL;

	if (fp) {
		fseek(fp, 0 , SEEK_END);
		filesize = ftell(fp);
		fseek(fp, 0 , SEEK_SET);
		pData = new unsigned char[filesize + padding];
		size_t read = fread(pData, 1, filesize, fp);
		if (read != filesize) {
			log(LOG_WARNING, "Could not read '%s' (got %d bytes instead of %d)", filename.c_str(), read, filesize);
		}
		fclose(fp);
	}

	return pData;
}
