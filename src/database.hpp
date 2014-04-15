#ifndef ULTRA_DATABASE

#define ULTRA_DATABASE	1

/**
 * This is a fairly basic name-value store. I have no plans to make it relational,
 * although I expect naming conventions to indicate basic relations, where
 * appropriate.
 */

#include "types.hpp"
#include "output/base.hpp"

typedef std::map<sgxString, sgxString > DBNameValueMap;

class DBEntry;


class UltraConfig;

class UltraDB {
public:
	UltraDB();
	~UltraDB();

	bool	import(const sgxString &filename);

	void	add(const sgxString &name, const sgxString &value);
	void	deleteNode(const sgxString &name);

	int 	getChildCount(const sgxString &name) const;

	bool	getString(const sgxString &name, sgxString &value) const;
	bool	getInteger(const sgxString &name, int &value) const;
	bool	getBoolean(const sgxString &name, bool &value) const;

	void	incInteger(const sgxString &name, int byAmount);

	bool	serializeAllTables(const sgxString &dirname) const;

	void	dumpTables(sgxString &output, const sgxString &separator) const;

#if ULTRA_DEBUG==1
	bool	serializeAll(const sgxString &filename) const;
#endif

private:
	DBNameValueMap		m_Data;
	DBEntry *			m_pDataRoot;


	DBEntry *		getNodeAndCreate(const sgxString &name);
	const DBEntry *	getNode(const sgxString &name) const;
		  DBEntry *	getNode(const sgxString &name);
	void			deleteNode(DBEntry *pNode);


	bool	serializeTable(UOutput &output, const DBEntry *pNode, const sgxString &stub, const sgxString &separator = "") const;


};



#endif
