#include "base.hpp"
#include "file.hpp"

#include <stdio.h>
#include <libio.h>

UOutputFilePointer::UOutputFilePointer(FILE *fp) {
	m_pFile = fp;
}

UOutputFilePointer::~UOutputFilePointer() {
	close();
}

void
UOutputFilePointer::close() {
	if (m_pFile) {
		::fclose(m_pFile);
		m_pFile = NULL;
	}
}


bool
UOutputFilePointer::write(const char *s) {
	return ::fputs(s, m_pFile) == EOF ? false : true;
}

bool
UOutputFilePointer::write(const char *s, const int count) {
	// TODO: Implement this!
	return false;
}

