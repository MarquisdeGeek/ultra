#ifndef ULTRA_OUTPUT_BASE

#define ULTRA_OUTPUT_BASE	1


class UOutput {
public:
	virtual ~UOutput() {}

	virtual bool write(const char *s) = 0;

	// TODO: I'm thinking of deprecated this version, or at least changing it, since
	// it's only really used as a write for the socket version.
	virtual bool write(const char *s, const int count) = 0;
};

#endif
