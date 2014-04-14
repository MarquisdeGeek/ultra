#ifndef ULTRA_UTILS

#define ULTRA_UTILS	1

#include "types.hpp"
#include <vector>

void intToString(sgxString &result, const int value);
int  splitString(std::vector<sgxString> &result, const sgxString &source, const char delimiter);

// 'padding' is a bad hack to allow the caller to slurp ASCII files
// by appending a NUL terminator to the data.
unsigned char *slurp(const sgxString &filename, size_t &filesize, size_t padding);

#endif
