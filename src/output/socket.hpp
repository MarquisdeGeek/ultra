#if ULTRA_OUTPUT_SOCKET==0

#define ULTRA_OUTPUT_SOCKET	1


class UOutputSocket : public UOutput {
public:
	UOutputSocket(int cfd);
	virtual ~UOutputSocket();

   virtual bool write(const char *s);
   virtual bool write(const char *s, const int count);
private:
	int cfd;
};

#endif
