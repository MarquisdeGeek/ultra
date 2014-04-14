#ifndef ULTRA_RESPONSE_HTML

#define ULTRA_RESPONSE_HTML	1

#include "types.hpp"
#include "response.hpp"

class UltraConfigBase;
class UltraConfig;
class UltraRequest;
class UOutput;
class UltraLine;


class UltraResponseText : public UltraResponse {
public:
	UltraResponseText(const UltraConfig *pConfig, const sgxString &filename);
	virtual ~UltraResponseText();

	bool	isBinaryAsset() const;

	virtual bool	writeBody(UOutput *pOutput, const UltraRequest *pRequest = NULL) const;

	UltraLine *				m_pContentRoot;

protected:

	unsigned char *	parse(UltraLine *pParent, UltraLine *pCurrentNode, unsigned char *pData);	// returns a ptr to the next character to parse

};


// TODO: Move this into the .cpp to become opaque.
// It's not currently done because SSI cheats during its process
class UltraLine {
public:
	UltraLine(UltraLine *pParent);

	void	addChild(UltraLine *pParent);
	bool	process(sgxString &result, const UltraConfig *pConfig, const UltraRequest *pRequest) const;

	sgxString					m_szLine;
	bool						m_bIsMeta;		// indicates that post-processing needs to take place on szLine
private:
	UltraLine *					m_pParent;
	std::vector<UltraLine *>	m_Children;
};




#endif
