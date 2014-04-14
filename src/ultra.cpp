/*
 * Ultra - Copyright 2014 Steven Goodwin. Released under the GNU GPL, version 3
 * Version 0.1
 *
 */

#include <sys/socket.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>

#include <stdarg.h>

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "version.hpp"

#include "ultra.hpp"
#include "output/output.hpp"
#include "database.hpp"
#include "config.hpp"
#include "service.hpp"



Service *				g_pData;

namespace {
	UltraConfigSettings * 	g_pConfiguration;
	int						g_LogSeverity;
}



void setLogLevel(const int severity) {
	g_LogSeverity = severity;
}

void log(const int severity, const char *format, ...) {
#if UBUILD_SUPPORT_LOGGING==UBUILD_LOGGING_FULL

	if (severity < g_LogSeverity) {
		return;
	}
	char buffer[4096];
	va_list args;
	va_start(args, format);
	vsprintf(buffer,format, args);
	if (severity == LOG_ERROR) {
		fprintf(stderr, "%s\n", buffer);
	} else {
		fprintf(stdout, "%s\n", buffer);
	}
	va_end(args);

#endif
}

void log(const int severity, const sgxString &format, ...) {
#if UBUILD_SUPPORT_LOGGING==UBUILD_LOGGING_FULL

	if (severity < g_LogSeverity) {
		return;
	}
	char buffer[4096];
	va_list args;
	va_start(args, format);
	vsprintf(buffer,format.c_str(), args);
	if (severity == LOG_ERROR) {
		fprintf(stderr, "%s\n", buffer);
	} else {
		fprintf(stdout, "%s\n", buffer);
	}
	va_end(args);

#endif
}



void
handleSerialize(int signum) {
#if UBUILD_SUPPORT_RESAVE==1
	if (g_pData) {
		log(LOG_INFO, "About to serialize existing DB to disc..");
		g_pData->serialize();
		log(LOG_INFO, "Serialize complete!");
	}
#else
	log(LOG_ERROR, "UBUILD_SUPPORT_RESAVE has been disabled.");
#endif
}

void handleReload(int signum) {
#if UBUILD_SUPPORT_RELOAD==1

	// If we don't serialize our data, we lose it upon the reload!
	handleSerialize(signum);

	// Load a duplicate copy of the data
	Service *pReplacement = g_pData->replicate();

	log(LOG_INFO, "Switching over to new service..");

		Service *pPrevious = g_pData;
		g_pData = pReplacement;
		delete pPrevious;

	log(LOG_INFO, "Done!");
#else
	log(LOG_ERROR, "UBUILD_SUPPORT_RELOAD has been disabled!");
#endif
}

void prepareSignalHandlers() {
	log(LOG_INFO, "Preparing signal handlers...");

#if UBUILD_SUPPORT_RELOAD==1
	if (signal(SIGHUP, handleReload) == SIG_IGN) {
		 signal(SIGHUP, SIG_IGN);
	}
#endif

#if UBUILD_SUPPORT_RESAVE==1
	if (signal(SIGUSR1, handleSerialize) == SIG_IGN) {
		 signal(SIGUSR1, SIG_IGN);
	}
#endif
	signal(SIGCHLD, SIG_IGN);
}

void test() {
	sgxString v;
	UltraDB *pDB = new UltraDB();
	pDB->add("table.1.name", "steev");
	pDB->add("table.1.age", "27");
	pDB->add("table.2.age", "37");
	pDB->getString("table.1.name", v);
	delete pDB;

	g_pData->m_pData->add("users.3.name", "333");
	//g_pData->m_pData->add("newtable.0.name", "added02020");
	//g_pData->m_pData->getString("users.3.name", v);
	g_pData->serialize();

	UOutputStdout *out = new UOutputStdout();
	g_pData->buildPage(out, "/");
	g_pData->buildPage(out, "/default.htm");
	g_pData->buildPage(out, "/one.htm");
	delete out;
}

int main(int argc, const char *argv[])
{
	sgxString siteRoot("site");
	sgxString sSiteConfig("default");

	if (argc > 1) {
		siteRoot = argv[1];
	}
	if (argc > 2) {
		sSiteConfig = argv[2];
	}

	log(LOG_INFO, ULTRA_VERSION);

	g_pConfiguration = new UltraConfigSettings(siteRoot, sSiteConfig);
	g_pData = Service::build(g_pConfiguration);

	if (!g_pData) {
		log(LOG_ERROR, "Configuration data and structure is invalid");
		return -1;
	}


	if (argc > 3 && strcmp(argv[3], "test") == 0)  {
		log(LOG_INFO, "Start test");
		test();
		log(LOG_INFO, "End test");
		return 0;
	}
	//
	size_t maxRequestSize = 128 * 1024;
	bool useFork = true;
	int port = 8088;
	g_pData->m_pConfig->getInteger("port", port);
	g_pData->m_pConfig->getBoolean("usefork", useFork);
	g_pData->m_pConfig->getSizeType("maxrequestsize", maxRequestSize);

	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in serv_addr;
	bzero((char *)&serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(port);

	if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr))) {
		log(LOG_ERROR, "Can't bind to port.");
		log(LOG_ERROR, strerror(errno));
		return -1;
	}
	listen(sockfd, 5);

	prepareSignalHandlers();

	// Use the PID:
	// kill -SIGHUP PID 	; to reload the config
	// kill -SIGUSR1 PID	; resave the DB to disc
	// We could write this into /var/run/ultra.pid (or a local file)
	printf("PID = %d\n", getpid());

	// A reminder of the port
	printf("Port = %d\n", port);
	log(LOG_INFO, "Running...");

	while (1) {
		struct sockaddr_in clientaddr;
		socklen_t clientaddr_sz = sizeof(clientaddr);

		int cfd  = accept(sockfd, (struct sockaddr*)&clientaddr, &clientaddr_sz);

#if UBUILD_REQUEST_HANDLER==UBUILD_REQUEST_SINGLE_THREAD
		int pid = 0;
		useFork = false;

#elif UBUILD_REQUEST_HANDLER==UBUILD_REQUEST_FORKED
		int pid = useFork ? fork() : 0;

#elif UBUILD_REQUEST_HANDLER==UBUILD_REQUEST_MULTI_THREADED
		// TODO: Use a pool of threads to save the time of creating new
		// processes all the time.
		int pid = 0;
		useFork = false;
		log(LOG_ERROR, "Multi-threaded is not yet supported");
#else
		int pid = 0;
		useFork = false;
		log(LOG_ERROR, "This type of handler is not yet supported");
#endif

		switch(pid) {
			case 0:
					{
					UOutput *pOut = new UOutputSocket(cfd);
					char buffer[2048];	// Most (all?) requests fit inside this buffer
					buffer[sizeof(buffer)-1] = '\0';
					size_t bytes;

					bytes = read(cfd, buffer, sizeof(buffer)-1);
					if (bytes == sizeof(buffer)-1) {
						// use slow path - probably trying to squeeze data through

						// TODO: If packet is an exact multiple of the buffer size, read() will block indefinitely
						sgxString bigBuffer(buffer);
						while((bytes = read(cfd, buffer, sizeof(buffer)-1)) > 0) {
							buffer[bytes] = '\0';
							bigBuffer += buffer;
							if (bigBuffer.length() > maxRequestSize) {
								// TODO: build a sensible error page
								break;
							}
						}
						g_pData->buildPage(pOut, bigBuffer.c_str());

					} else {	// use fast path
						g_pData->buildPage(pOut, buffer);
					}
					delete pOut;

					if (useFork) {
						_exit(EXIT_SUCCESS);
					}
					}
					break;

			case -1:
				log(LOG_ERROR, "Error with fork");
				break;
		}

		waitpid(-1, NULL, 1/*WNOHANG*/);
	}
 
	return 0;
}
