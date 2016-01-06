#pragma once

#include "WindowsTCPServer.h"
#include "LinuxTCPServer.h"

class myTCPServer :
#ifdef _WIN32
	public WindowsTCPServer
#else
	public LinuxTCPServer
#endif
{
public:
	~myTCPServer() {};
};
