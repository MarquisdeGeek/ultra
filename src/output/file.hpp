#if ULTRA_OUTPUT_FILE==0

#define ULTRA_OUTPUT_FILE	1

#include <stdio.h>

class UOutputFilePointer  : public UOutput {
public:
	UOutputFilePointer(FILE *fp);
	virtual ~UOutputFilePointer();

	virtual bool write(const char *s);
	virtual bool write(const char *s, const int count);

	void close();

private:
	FILE *		m_pFile;
};

#endif
