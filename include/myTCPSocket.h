#pragma once

#ifdef _WIN32

# include <winsock2.h>
# include <ws2tcpip.h>
# include <windows.h>

#else
# include <netinet/in.h>
# include <sys/types.h>
# include <sys/socket.h>
#endif

#include "WindowsTCPSocket.h"
#include "LinuxTCPSocket.h"

class myTCPSocket :
#ifdef _WIN32
	public WindowsTCPSocket
#else
	public LinuxTCPSocket
#endif
{
public:
	myTCPSocket(){};
#ifdef _WIN32
	myTCPSocket(struct sockaddr_in &addr, int fd) :
		WindowsTCPSocket(addr, fd) {}
#else
	myTCPSocket(struct sockaddr_in &addr, int fd) :
		LinuxTCPSocket(addr, fd) {}
#endif
	~myTCPSocket(){};
};
