#include "ultra.hpp"
#include "database.hpp"
#include "config.hpp"

#include "request.hpp"


// TODO: Incoporate all features from here:
// http://en.wikipedia.org/wiki/URL_normalization
UltraRequest::UltraRequest(const sgxString &req, const UltraConfig *pConfig) : m_pConfig(pConfig) {
	const int PARSE_VERB = 0;
	const int PARSE_URL = 1;
	const int PARSE_ARGUMENTS = 2;

	int parseState = PARSE_VERB;
	sgxString s;
	sgxString name;

	const char *p = req.c_str();
	bool bExitLoop = false;
	while(*p && !bExitLoop) {
		switch(*p) {
		case '?':
			m_URL = s;
			parseState = PARSE_ARGUMENTS;
			s = "";
			break;

		case '=':
			name = s;
			s = "";
			break;

		case ' ':
			switch(parseState) {
			case PARSE_VERB:
				m_Verb = s;
				s = "";
				parseState = PARSE_URL;
				break;

			case PARSE_URL:
				// only triggers when there are no args. Otherwise, case '?' switches into state 2
				m_URL = s;
				bExitLoop = true;
				break;

			case PARSE_ARGUMENTS:
				// this space indicates the http component - which we'll ignore for now.
				// We know there's an argument present because otherwise, we'd in be state 3, so
				// add that to the DB
				m_pConfigData->add(name, s);
				bExitLoop = true;
				break;
			}
			break;

		case '&':	// moving to second and subsequent arguments - flush the previous arg
			m_pConfigData->add(name, s);
			s = "";
			break;

		default:	// TODO: Better handle encoding in the URL
			s += *p == '+' ? ' ' : *p;
		}
		//
		++p;
	}

	if (m_URL == "") {	// If URL is empty, then the '?' didn't appear, and there are no arguments
		m_URL = s;
	}

	if (m_URL == "/") {
		m_URL = "default.htm";	// this is the default, if the config doesn't replace it in getString, we use it
		pConfig && pConfig->getString(sgxString("root"), m_URL);
		m_URL = "/" + m_URL;
	}

}

UltraRequest::~UltraRequest() {

}


bool
UltraRequest::getString(const sgxString &name, sgxString &value) const {
	return m_pConfigData->getString(name, value);
}
