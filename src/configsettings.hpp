#ifndef ULTRA_CONFIG_SETTINGS

#define ULTRA_CONFIG_SETTINGS	1


class UltraConfigSettings {
public:
	sgxString 	m_RootPath;
	sgxString 	m_Configuration;

	UltraConfigSettings(const sgxString &root, const sgxString &config) :
		m_RootPath(root),
		m_Configuration(config) {
	}
};


#endif
