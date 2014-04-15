#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#include "ultra.hpp"
#include "database.hpp"

#include "remap/remap.hpp"

#include "config.hpp"
#include "request.hpp"


UltraConfigBase::UltraConfigBase()  {
	m_pConfigData = new UltraDB();
	m_pNullRemap = new UltraRemapNull();
}

UltraConfigBase::~UltraConfigBase() {
	// Clear the remap objects
	StaticMap::iterator it1 = m_Mapper.begin();
	for(;it1!=m_Mapper.end();++it1) {
		delete (*it1).second;
	}
	m_Mapper.clear();

	StaticMap::iterator it2 = m_MapperWildcards.begin();
	for(;it2!=m_MapperWildcards.end();++it2) {
		delete (*it2).second;
	}
	m_MapperWildcards.clear();

	// Clear the rest
	delete m_pNullRemap;
	delete m_pConfigData;

	m_pConfigData = NULL;
	m_pNullRemap = NULL;
}

const UltraRemap *
UltraConfigBase::getNullRemap() const {
	return m_pNullRemap;
}

const UltraRemap *
UltraConfigBase::getRemap(const sgxString &source) const {

	// Look for an exact mapping
	if (m_Mapper.find(source) != m_Mapper.end() ) {
		return m_Mapper.at(source);
	}

	// Try the wildcard list
	StaticMap::const_iterator it = m_MapperWildcards.begin();
	for(;it != m_MapperWildcards.end(); ++it) {
		if (source.compare(0, (*it).first.length(), (*it).first) == 0) {
			return (*it).second;
		}
	}

	return NULL;
}

void
UltraConfigBase::getRemapString(sgxString &target, const sgxString &source) const {
	// Look for an exact mapping
	if (m_Mapper.find(source) != m_Mapper.end() ) {
		return m_Mapper.at(source)->process(target, source);
	}

	// Try the wildcard list
	StaticMap::const_iterator it = m_MapperWildcards.begin();
	for(;it != m_MapperWildcards.end(); ++it) {
		if (source.compare(0, (*it).first.length(), (*it).first) == 0) {
			sgxString param = source.substr((*it).first.length());
			return (*it).second->process(target, param);
		}
	}

	// Replace with the string itself
	target = source;
}

void
UltraConfigBase::addRemap(const sgxString &source, const UltraRemap *pRemap) {
	m_Mapper[source] = pRemap;
}

void
UltraConfigBase::addRemap(const char *pSource, const UltraRemap *pRemap) {
	m_Mapper[sgxString(pSource)] = pRemap;
}

void
UltraConfigBase::addRemapWildcard(const char *pSource, const UltraRemap *pRemap) {
	m_MapperWildcards[sgxString(pSource)] = pRemap;
}


bool
UltraConfigBase::getString(const sgxString &name, sgxString &value) const {
	if (m_pConfigData->getString(name, value)) {
		return true;
	}
	return false;
}

bool
UltraConfigBase::getInteger(const sgxString &name, int &value) const {
	sgxString v;
	if (getString(name, v)) {
		value = atoi(v.c_str());
		return true;
	}
	return false;
}

bool
UltraConfigBase::getSizeType(const sgxString &name, size_t &value) const {
	sgxString v;
	if (getString(name, v)) {
		value = atoi(v.c_str());
		return true;
	}
	return false;
}

bool
UltraConfigBase::getBoolean(const sgxString &name, bool &value) const {
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

