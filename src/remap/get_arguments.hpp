#ifndef ULTRA_REMAP_GET_ARGUMENTS

#define ULTRA_REMAP_GET_ARGUMENTS		1


class UltraRequest;

class UltraRemapGetArguments : public UltraRemap {
public:
	UltraRemapGetArguments(const UltraRequest &request);

	virtual void		process(sgxString &resultPattern, const sgxString &source) const;

private:
	const UltraRequest &	m_Request;
};


#endif
