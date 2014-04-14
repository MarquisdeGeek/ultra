#ifndef ULTRA

#define ULTRA	1

#include "types.hpp"
#include "settings.hpp"


#define LOG_ERROR		2
#define LOG_WARNING		1
#define LOG_INFO		0

void setLogLevel(const int severity);
void log(const int severity, const char *format, ...);
void log(const int severity, const sgxString &format, ...);

#endif
