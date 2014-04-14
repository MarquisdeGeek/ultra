#ifndef ULTRA_FILESET

#define ULTRA_FILESET	1

// Note: settings required to compile in/out the mutex lock
#include "settings.hpp"

class UltraResponse;
typedef std::map<sgxString, UltraResponse *> PageMap;


class UltraFileSet {
public:
	UltraFileSet(const UltraConfig *pConfig);
	~UltraFileSet();

	void	loadFiles(const UltraConfig *pConfig);
	void	preProcessPages();

public:
	PageMap			m_PageList;
	PageMap			m_AssetList;
	PageMap			m_DBList;

private:
	const UltraConfig *	m_pConfig;

#if UBUILD_LOCK_DATA_CHANGES==1
	pthread_mutex_t 	m_Lock;
#endif
};


#endif
