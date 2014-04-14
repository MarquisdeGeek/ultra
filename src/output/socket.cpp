#include "../ultra.hpp"

#include "base.hpp"
#include "socket.hpp"

#include <sys/socket.h>


#include<stdio.h>
#include<string.h>
#include<stdlib.h>


#include<unistd.h>
#include<sys/types.h>


UOutputSocket::UOutputSocket(int cfd) {
	this->cfd = cfd;
}

UOutputSocket::~UOutputSocket() {
	shutdown(cfd, SHUT_RDWR);
	close(cfd);
}

bool
UOutputSocket::write(const char *s) {
	size_t bytesToWrite = strlen(s);
	size_t bytesWritten = ::send(cfd, s, bytesToWrite, MSG_MORE);

	if (bytesWritten == (size_t)-1 || bytesWritten != bytesToWrite) {
		return false;
	}
	return true;
}

bool
UOutputSocket::write(const char *s, const int count) {
	return ::write(cfd, s, count) == count ? true : false;
}

