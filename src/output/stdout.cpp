#include "base.hpp"
#include "stdout.hpp"
#include <stdio.h>

// TODO: Fold this into output_file(stdout)
UOutputStdout::~UOutputStdout() {
} 

bool
UOutputStdout::write(const char *s) {
   ::puts(s);
   return true;
} 

bool
UOutputStdout::write(const char *s, const int count) {
	// TODO: FIXME
	::puts(s);
	return true;
} 

