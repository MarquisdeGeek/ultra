#if ULTRA_OUTPUT_STDIN==0

#define ULTRA_OUTPUT_STDIN	1

class UOutputStdout  : public UOutput {
public:
	virtual ~UOutputStdout();

	virtual bool write(const char *s);
	virtual bool write(const char *s, const int count);
};

#endif
