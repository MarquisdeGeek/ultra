#include "base.hpp"
#include "time.hpp"

#include <strstream>

UltraRemapTime::UltraRemapTime(int field) {
	m_Field = field;
}

void
UltraRemapTime::process(sgxString &resultPattern, const sgxString &source) const {
time_t t = time(0);
struct tm *now = localtime(&t);
std::strstream temp;

	switch(m_Field) {
	case 0:		temp << now->tm_hour;		break;
	case 1:		temp << now->tm_min;		break;
	case 2:		temp << now->tm_sec;		break;
	case 3:		temp << now->tm_year;		break;
	case 4:		temp << now->tm_mon;		break;
	case 5:		temp << now->tm_mday;		break;
	}

	temp >> resultPattern;
}
