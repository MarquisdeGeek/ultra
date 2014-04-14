#ifndef ULTRA_CONFIG

#define ULTRA_CONFIG	1

#include "types.hpp"

#include "configsettings.hpp"
#include "configbase.hpp"

class UltraConfig : public UltraConfigBase {
public:
	UltraConfig(const UltraConfigSettings *pConfigSettings, UltraDB *pDatabase);

			void	getRootPath(sgxString &root) const;

	virtual bool	getString(const sgxString &name, sgxString &value) const;
			bool	getContentType(sgxString &type, const sgxString &filename) const;

public:
	UltraDB *			m_pAccessStats;			// dynamically updated on each request, globally
	UltraDB *			m_pMIMETypes;
	UltraDB *			m_pDatabase;

private:
	const sgxString 	m_Mode;
	const sgxString		m_RootPath;


};




#endif
