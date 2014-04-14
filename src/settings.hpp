#ifndef ULTRA_SETTINGS

#define ULTRA_SETTINGS 1



/*
 * ULTRA_DEBUG
 *
 * Switches on additional logging and DB dump information.
 *
 */
#ifndef ULTRA_DEBUG
#define ULTRA_DEBUG		0
#endif


/**
 * All meta-symbols, which get remapping to DB entries, are wrapper {(like this)}
 */
#define ULTRA_META_OPEN1	'{'
#define ULTRA_META_OPEN2	'('
#define ULTRA_META_CLOSE1	')'
#define ULTRA_META_CLOSE2	'}'


/*
 * UBUILD_SUPPORT_RESAVE
 *
 * Allows Ultra to re-export the DB to disc, if appropriate.
 * Will not work on fileblock configurations (because there's no
 * disc to save back to)
 *
 */
#ifndef UBUILD_SUPPORT_RESAVE
#define UBUILD_SUPPORT_RESAVE	1
#endif


/*
 * UBUILD_SUPPORT_RELOAD
 *
 * Respond to SIGHUP to reload the configuration. If disabled, SIGHUP does a
 * traditional hangup. i.e. it terminates
 */
#ifndef UBUILD_SUPPORT_RELOAD
#define UBUILD_SUPPORT_RELOAD	1
#endif


/*
 * UBUILD_SUPPORT_EXCEPTIONS
 *
 * Include try-catch around the page handler. Use for C++ and/or you're using
 * fork() and dangerous process that might crash.
 */
#ifndef UBUILD_SUPPORT_EXCEPTIONS
#define UBUILD_SUPPORT_EXCEPTIONS	1
#endif


/*
 * UBUILD_SUPPORT_ACCESS_STATS
 *
 * Builds a DB table of every page access and error
 */
#ifndef UBUILD_SUPPORT_ACCESS_STATS
#define UBUILD_SUPPORT_ACCESS_STATS	1
#endif




/*
 * UBUILD_LOCK_DATA_CHANGES
 *
 * Add mutexes around any change or access to the database.
 */
#ifndef UBUILD_LOCK_DATA_CHANGES
#define UBUILD_LOCK_DATA_CHANGES	1
#endif


/*
 * UBUILD_SUPPORT_DATABASE_IMPLEMENTATION
 *
 * Which method of internal DB is used. You need some knowledge about the
 * internals to make sensible use of this.
 */
#define UBUILD_DB_NONE		0
#define UBUILD_DB_FLAT		1
#define UBUILD_DB_HIERARCHY	2

#ifndef UBUILD_SUPPORT_DATABASE_IMPLEMENTATION
#define UBUILD_SUPPORT_DATABASE_IMPLEMENTATION	UBUILD_DB_HIERARCHY
#endif


/*
 * UBUILD_SUPPORT_LOGGING
 *
 * Include try-catch around the page handler. Use for C++ and/or you're using
 * fork() and dangerous process that might crash.
 */
#define UBUILD_LOGGING_NONE		0
#define UBUILD_LOGGING_FULL		1

#ifndef UBUILD_SUPPORT_LOGGING
#define UBUILD_SUPPORT_LOGGING	UBUILD_LOGGING_FULL
#endif

/*
 * UBUILD_REQUEST_HANDLER
 *
 * How should each HTTP request be dispatched?
 */
#define UBUILD_REQUEST_SINGLE_THREAD	0
#define UBUILD_REQUEST_FORKED			1
#define UBUILD_REQUEST_MULTI_THREADED	2

#ifndef UBUILD_REQUEST_HANDLER
#define UBUILD_REQUEST_HANDLER	UBUILD_REQUEST_SINGLE_THREAD
#endif

// TODO: Not implemented
#ifndef UBUILD_REQUEST_THREAD_COUNT
#define UBUILD_REQUEST_THREAD_COUNT		16
#endif



/*
 * UBUILD_FILESYSTEM
 *
 * Where is the filesystem data stored, and in which format.
 */
#define UBUILD_FILESYSTEM_NONE		0
#define UBUILD_FILESYSTEM_DIRECTORY	1
#define UBUILD_FILESYSTEM_FILEBLOCK	2

#ifndef UBUILD_FILESYSTEM
#define UBUILD_FILESYSTEM		UBUILD_FILESYSTEM_DIRECTORY
#endif





#endif
