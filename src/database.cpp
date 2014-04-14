#include "ultra.hpp"
#include "output/output.hpp"
#include "database.hpp"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <algorithm>

#include <sstream>
#include <iterator>

class DBEntry {
public:
	DBEntry(DBEntry *pParent, const sgxString &name="", const sgxString &value="");
	~DBEntry();

		  DBEntry * 	getChild(const sgxString &name);
	const DBEntry * 	getChild(const sgxString &name) const;
			int 		getChildCount() const;

			void		removeChild(DBEntry *pNode);

			sgxString	name;
			sgxString	value;
			std::vector<DBEntry *>	children;
			DBEntry *				m_pParent;
			//
	unsigned long	nextEntry;
};



DBEntry::DBEntry(DBEntry *pParent, const sgxString &name_, const sgxString &value_) {
	name = name_;
	value = value_;

	nextEntry = 0;
	m_pParent = pParent;
}

DBEntry::~DBEntry() {
	std::vector<DBEntry *>::const_iterator cit = children.begin();

	for(;cit!=children.end();++cit) {
		delete (*cit);
	}
}

const DBEntry *
DBEntry::getChild(const sgxString &name) const {
	std::vector<DBEntry *>::const_iterator cit = children.begin();

	for(;cit!=children.end();++cit) {
		if (name == (*cit)->name) {
			return (*cit);
		}
	}
	return NULL;
}

DBEntry *
DBEntry::getChild(const sgxString &name) {
	std::vector<DBEntry *>::iterator it = children.begin();

	for(;it!=children.end();++it) {
		if (name == (*it)->name) {
			return (*it);
		}
	}
	return NULL;
}

int
DBEntry::getChildCount() const {
	return children.size();
}

void
DBEntry::removeChild(DBEntry *pNode) {
	std::vector<DBEntry *>::iterator nodeIterator = find(children.begin(), children.end(), pNode);

	if(nodeIterator!=children.end()) {
		children.erase(nodeIterator);
	}
}


//
//
//

UltraDB::UltraDB() {
	m_pDataRoot = new DBEntry(NULL);
}

bool
UltraDB::import(const sgxString &filename) {
	bool rt = true;

	FILE *fp = fopen(filename.c_str(), "r");
	if (fp) {
		char buffer[160];	// TODO:BUGWARN
		buffer[sizeof(buffer)-1] = '\0';// this and the sizeof-1 ensure the last
		//character is always nul, and always present. Stops strchr et al running past the end of the string

		while(fgets(buffer, sizeof(buffer)-1, fp)) {
			char *pToken = strchr(buffer, '=');
			if (pToken) {
				// poor mans trim()
				char *pCR = strchr(buffer,'\n');
				if (pCR != NULL) {
					*pCR = '\0';
				}

				*pToken = '\0';
				add(sgxString(buffer), sgxString(pToken+1));
			} else {
				// TODO: Warning. invalid name:value pair at line X in file F
				rt = false;
			}

		}
		fclose(fp);
		return rt;
	}

	return false;
}

int
UltraDB::getChildCount(const sgxString &name) const {
	const DBEntry *pNode = getNode(name);

	return pNode ? pNode->getChildCount() : 0;
}


DBEntry *
UltraDB::getNodeAndCreate(const sgxString &name) {
	DBEntry *pRoot = m_pDataRoot;
	DBEntry *pNext;

	// Find the root
	sgxString word;
	std::stringstream streamtxt(name);
	while( std::getline(streamtxt, word, '.') ) {
		pNext = pRoot->getChild(word);
		if (pNext) {
			pRoot = pNext;
		} else {
			DBEntry *pNewNode = new DBEntry(pRoot, word, "");

			pRoot->children.push_back(pNewNode);
			pRoot = pNewNode;
		}
	}

	return pRoot;
}

const DBEntry *
UltraDB::getNode(const sgxString &name) const {
	const DBEntry *pRoot = m_pDataRoot;
	const DBEntry *pNext;

	// Find the root
	sgxString word;
	std::stringstream stream(name);
	while( std::getline(stream, word, '.') ) {
		pNext = pRoot->getChild(word);
		if (pNext) {
			pRoot = pNext;
		} else {	// it doesn't exist
			return NULL;
		}
	}

	return pRoot;
}

DBEntry *
UltraDB::getNode(const sgxString &name) {
	DBEntry *pRoot = m_pDataRoot;
	DBEntry *pNext;

	// Find the root
	sgxString word;
	std::stringstream stream(name);
	while( std::getline(stream, word, '.') ) {
		pNext = pRoot->getChild(word);
		if (pNext) {
			pRoot = pNext;
		} else {	// it doesn't exist
			return NULL;
		}
	}

	return pRoot;
}

void
UltraDB::incInteger(const sgxString &name, int byAmount) {
	DBEntry *pNode = getNodeAndCreate(name);
	int current = atoi(pNode->value.c_str());
	current += byAmount;

	std::stringstream convert;
	convert << current;
	pNode->value = convert.str();
}

void
UltraDB::add(const sgxString &name, const sgxString &value) {

#if UBUILD_SUPPORT_DATABASE_IMPLEMENTATION==UBUILD_DB_HIERARCHY
	DBEntry *pNode = getNodeAndCreate(name);

	pNode->value = value;
#endif

#if UBUILD_SUPPORT_DATABASE_IMPLEMENTATION==UBUILD_DB_FLAT
	// Store in flat structure
	m_Data[name] = value;
#endif
}

bool
UltraDB::getString(const sgxString &name, sgxString &value) const {

#if UBUILD_SUPPORT_DATABASE_IMPLEMENTATION==UBUILD_DB_HIERARCHY
	const DBEntry *pNode = getNode(name);
	if (pNode) {
		value = pNode->value;
		return true;
	}
	return false;
#endif

#if UBUILD_SUPPORT_DATABASE_IMPLEMENTATION==UBUILD_DB_FLAT
	if (m_Data.find(name) == m_Data.end() ) {
		return false;
	}

	// NOte: Use 'at' instead of [] because 'at' doesn't create non-existent fields
	value = m_Data.at(name);
	return true;
#endif
}


bool
UltraDB::getInteger(const sgxString &name, int &value) const {
	sgxString v;
	if (getString(name, v)) {
		value = atoi(v.c_str());
		return true;
	}
	return false;
}

bool
UltraDB::getBoolean(const sgxString &name, bool &value) const {
	sgxString v;
	if (getString(name, v)) {
		std::transform(v.begin(), v.end(), v.begin(), ::tolower);

		if (v == "true" || v == "yes" || v == "1") {
			value = true;
		}
		value = atoi(v.c_str()) ? true : false;
		return true;
	}
	return false;
}


void
UltraDB::deleteNode(const sgxString &name) {
	DBEntry *pNode = getNode(name);
	deleteNode(pNode);
}

void
UltraDB::deleteNode(DBEntry *pNode) {
	if (!pNode) {
		return;
	}
	//
	pNode->m_pParent->removeChild(pNode);
	//
	delete pNode;
}


bool
UltraDB::serializeTable(UOutput &output, const DBEntry *pNode, const sgxString &stub, const sgxString &separator) const {
	if (!pNode) {
		return true;
	}

	sgxString prefix(stub);

	if (prefix != "") {
		prefix += ".";
	}

	// Write this nodes name=value pair, and auxiliary information
	sgxString name = prefix + pNode->name;
	sgxString nv(name);
	nv += "=";
	nv += pNode->value;
	nv += separator;

	output.write(nv.c_str());
	// TODO: write counts and other meta data

	// Write all children
	bool rt = true;
	std::vector<DBEntry *>::const_iterator cit = pNode->children.begin();
	for(;cit!=pNode->children.end();++cit) {
		rt &= serializeTable(output, *cit, name, separator);
	}
	return rt;
}

void
UltraDB::dumpTables(sgxString &output, const sgxString &separator) const {

	sgxString result;
	UOutputString ofp(result);

	// Anything in the root is considered a table
	std::vector<DBEntry *>::const_iterator cit = m_pDataRoot->children.begin();
	for(;cit!=m_pDataRoot->children.end();++cit) {
		serializeTable(ofp, *cit, "", separator);
	}

	output += result;
}


bool
UltraDB::serializeAllTables(const sgxString &dirname) const {
#if UBUILD_SUPPORT_RESAVE==1
	std::vector<DBEntry *>::const_iterator cit = m_pDataRoot->children.begin();
	bool rt = true;

	// Anything in the root is considered a table
	for(;cit!=m_pDataRoot->children.end();++cit) {
		sgxString fullPath = dirname + "/" + (*cit)->name;
		sgxString tmpFullPath = fullPath + "~";
		FILE *fp = fopen(tmpFullPath.c_str(), "w+");
		if (fp) {
			UOutputFilePointer ofp(fp);

			rt &= serializeTable(ofp, *cit, "", "\n");

			ofp.close();
			//
			if (rt) {
				rename(tmpFullPath.c_str(),fullPath.c_str());
			} else {
				log(LOG_ERROR, "Unable to write %s", tmpFullPath.c_str());
			}

		} else {
			log(LOG_ERROR, "Unable to write to DB table file");
			rt = false;
		}

	}

	return rt;
#else
	return false;
#endif
}

#if ULTRA_DEBUG==1
bool
UltraDB::serializeAll(const sgxString &filename) const {
#if UBUILD_SUPPORT_RESAVE==1
	bool rt = true;

	FILE *fp = fopen(filename.c_str(), "w+");
	DBNameValueMap::const_iterator cit = m_Data.begin();
	for(;cit != m_Data.end();++cit) {
		sgxString nv(cit->first);
		nv += "=";
		nv += cit->second;
		nv += "\n";
		fputs(nv.c_str(), fp);
	}
	fclose(fp);

	return rt;
#else
	return false;
#endif
}
#endif
