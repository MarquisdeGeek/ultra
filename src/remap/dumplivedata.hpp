#ifndef ULTRA_REMAP_DUMPLIVEDATA

#define ULTRA_REMAP_DUMPLIVEDATA		1

class UltraDB;
class UltraRemapDumpDB;
class Service;

class UltraRemapDumpLiveData : public UltraRemapDumpDB {
public:
	UltraRemapDumpLiveData(UltraDB *pDatabase);
	virtual void		process(sgxString &resultPattern, const sgxString &source) const;
private:
	UltraDB *			m_pDatabase;
};

#endif
