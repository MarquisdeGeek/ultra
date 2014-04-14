#ifndef ULTRA_REMAP_DATABASE_FIELDCOUNT

#define ULTRA_REMAP_DATABASE_FIELDCOUNT		1

class UltraDB;

class UltraRemapDatabaseFieldCount : public UltraRemap {
public:
	UltraRemapDatabaseFieldCount(UltraDB *pData);

	virtual void		process(sgxString &resultPattern, const sgxString &source) const;

protected:
	UltraDB *	m_pData;
};
#endif
