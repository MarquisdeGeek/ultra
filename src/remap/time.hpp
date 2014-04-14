#ifndef ULTRA_REMAP_TIME

#define ULTRA_REMAP_TIME		1


class UltraRemapTime : public UltraRemap {
public:
	UltraRemapTime(int field);
	virtual void		process(sgxString &resultPattern, const sgxString &source) const;

private:
	int m_Field;
};

#endif
