#if ULTRA_OUTPUT_STRING==0

#define ULTRA_OUTPUT_STRING	1

class UOutputString  : public UOutput {
public:
	UOutputString(sgxString &result) : m_Result(result) {}
	virtual ~UOutputString() {}

	virtual bool write(const char *s) {
		m_Result += s;
		return true;
	}

	virtual bool write(const char *s, const int count) {
		// TODO: properly
		m_Result += s;
		return true;
	}

private:
	sgxString &		m_Result;
};

#endif
