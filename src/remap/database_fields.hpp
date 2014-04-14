#ifndef ULTRA_REMAP_DATABASE_FIELDS

#define ULTRA_REMAP_DATABASE_FIELDS		1


class UltraRemapDatabaseFields : public UltraRemap {
public:
	UltraRemapDatabaseFields(UltraDB *pData, bool silent);
	virtual void		process(sgxString &resultPattern, const sgxString &source) const;

protected:
	UltraDB *	m_pData;
	bool		m_bSilent;

};


#endif
