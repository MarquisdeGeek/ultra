#ifndef ULTRA_SERVICE

#define ULTRA_SERVICE	1

class UltraConfig;
class UltraDB;
class UltraFileSet;
class UOutput;

class UltraConfigSettings;

class Service {
public:
	UltraConfig *	m_pConfig;
	UltraDB *		m_pData;
	UltraFileSet *	m_pPages;

	Service(const UltraConfigSettings *pConfig);
	~Service();

	Service *	replicate();

	void		loadFiles();

	void		processPages();
	void		writeHeader(UOutput *pOutput, const int code);
	void		buildPage(UOutput *pOutput, const char *buffer);
	bool		serialize();


	static Service *	build(const UltraConfigSettings *pConfig);

private:

public:
	const UltraConfigSettings *m_pConfigSettings;
};



#endif
