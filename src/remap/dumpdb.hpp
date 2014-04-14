#ifndef ULTRA_REMAP_DUMPDB

#define ULTRA_REMAP_DUMPDB		1

class UltraDB;

class UltraRemapDumpDB : public UltraRemap {
public:
	UltraRemapDumpDB(const UltraDB *pDB);
	
	virtual void		process(sgxString &resultPattern, const sgxString &source) const;

private:
	const UltraDB *		m_pDatabase;
};

#endif
