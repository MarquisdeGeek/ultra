#ifndef ULTRA_CONFIG_BASE

#define ULTRA_CONFIG_BASE	1

class UltraRemap;
class UltraDB;

typedef std::map<const sgxString, const UltraRemap *> StaticMap;

// We use a config base separate from a basic configuration, so that we can have
// additional config-like classes, using the datastore.
class UltraConfigBase {
public:
	UltraConfigBase();
	virtual ~UltraConfigBase();

	void	addRemap(const sgxString &source, const UltraRemap *pRemap);
	void	addRemap(const char *pSource, const UltraRemap *pRemap);
	void	addRemapWildcard(const char *pSource, const UltraRemap *pRemap);

	const UltraRemap *	getRemap(const sgxString &source) const;
	const UltraRemap *	getNullRemap() const;

	void	getRemapString(sgxString &target, const sgxString &source) const;

	bool	getInteger(const sgxString &name, int &value) const;
	bool	getSizeType(const sgxString &name, size_t &value) const;
	bool	getBoolean(const sgxString &name, bool &value) const;

	// only getString is virtual, currently, because getInteger et al are expected to call this
	// method, and convert it into the correct type.
	virtual bool	getString(const sgxString &name, sgxString &value) const;

protected:
	UltraDB *			m_pConfigData;			// mostly const throughout its life, until restart
	UltraRemap *		m_pNullRemap;
private:
	StaticMap			m_Mapper;
	StaticMap			m_MapperWildcards;

};


#endif
