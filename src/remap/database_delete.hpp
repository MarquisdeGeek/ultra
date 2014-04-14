#ifndef ULTRA_REMAP_DATABASE_DELETE

#define ULTRA_REMAP_DATABASE_DELETE		1

class UltraDB;

class UltraRemapDatabaseDelete : public UltraRemap {
public:
	UltraRemapDatabaseDelete(UltraDB *pData);
	virtual void		process(sgxString &resultPattern, const sgxString &source) const;

protected:
	UltraDB *	m_pData;
};

#endif
