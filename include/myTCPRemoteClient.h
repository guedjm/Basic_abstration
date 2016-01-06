#pragma once

#include "LinuxTCPRemoteClient.h"
#include "WindowsTCPRemoteClient.h"

class myTCPRemoteClient :
#ifdef _WIN32
	public WindowsTCPRemoteClient
#else
	public LinuxTCPRemoteClient
#endif
{
public:
	myTCPRemoteClient(struct sockaddr_in &, int);
	virtual ~myTCPRemoteClient();
};
