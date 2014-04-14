#define _REENTRANT
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <iostream>
#include <sys/stat.h>
#include <ftw.h>
#include <pthread.h>

#include "ultra.hpp"
#include "database.hpp"
#include "config.hpp"

#include "response.hpp"
#include "response_text.hpp"
#include "response_binary.hpp"

#include "service.hpp"
#include "utils.hpp"

#include "fileset.hpp"

namespace {
	// Used only for the directory enumeration callback
	UltraFileSet * 		g_pPages;
	const UltraConfig *	g_pConfig;


	int buildCallback(const char *path, const struct stat *sptr, int type) {
		if (S_ISDIR(sptr->st_mode)) {
			return 0;
		}
		// BUGWARN: This is slow. It's only in the loader, and therefore rarely
		// called, but it's still an improvement.
		sgxString root;
		bool isBinary = false;

		// TODO: Need a better way to determine binary/ascii, to indicate
		// whether it should be processed.
		// I like the idea of separate docs/ and /assets folders, but not
		// sure if the populous will agree!
		const char *pDot = strrchr(path, '.');
		if (pDot) {
			if (strcmp(pDot, ".jpg") == 0  || strcmp(pDot, ".png") == 0 || strcmp(pDot, ".ico") == 0) {
				isBinary = true;
			}
		}

		//
		if (isBinary) {
			g_pPages->m_PageList[path] = new UltraResponseBinary(g_pConfig, path);
		} else {
			g_pPages->m_PageList[path] = new UltraResponseText(g_pConfig, path);
		}
		return 0;
	}

	int buildCallbackDatabase(const char *path, const struct stat *sptr, int type) {
		if (S_ISDIR(sptr->st_mode)) {
			return 0;
		}
		g_pPages->m_DBList[path] = new UltraResponseText(g_pConfig, path);
		return 0;
	}
}


UltraFileSet::UltraFileSet(const UltraConfig *pConfig) : m_pConfig(pConfig) {
#if UBUILD_LOCK_DATA_CHANGES==1
	pthread_mutex_init(&m_Lock, NULL);
#endif
}

UltraFileSet::~UltraFileSet() {
#if UBUILD_LOCK_DATA_CHANGES==1
	pthread_mutex_destroy(&m_Lock);
#endif
}


void
UltraFileSet::loadFiles(const UltraConfig *pConfig) {
#if UBUILD_LOCK_DATA_CHANGES==1
	pthread_mutex_lock(&m_Lock);
#endif

#if UBUILD_FILESYSTEM==UBUILD_FILESYSTEM_DIRECTORY

		g_pPages = this;
		g_pConfig = pConfig;

		// HTML docs & assets
		sgxString fileRoot;
		g_pConfig->getRootPath(fileRoot);
		fileRoot += "/docs";

		ftw(fileRoot.c_str(), buildCallback, 7);

#elif UBUILD_FILESYSTEM==UBUILD_FILESYSTEM_FILEBLOCK
		// TODO: Write fileblock code
		log(LOG_ERROR, "The fileblock filesystem has not yet been written.	");
#endif


#if UBUILD_SUPPORT_DATABASE_IMPLEMENTATION==UBUILD_DB_NONE
		// NOP
#else
		sgxString dbRoot;

		// DB files
		g_pConfig->getRootPath(dbRoot);
		dbRoot += "/db";

		ftw(dbRoot.c_str(), buildCallbackDatabase, 7);
#endif


#if UBUILD_LOCK_DATA_CHANGES==1
		pthread_mutex_unlock(&m_Lock);
#endif
}

void
UltraFileSet::preProcessPages() {

	// TODO - pre amend all the static changes. e.g. {home}, {link:} etc
	// to speed the page build up further.  This will require a new field
	// indicating whether the remap is dynamic (default true, for safety)
}


