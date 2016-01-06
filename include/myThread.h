#pragma once
#include "LinuxPThread.h"
#include "WindowsThread.h"

class myThread :
#ifdef _WIN32
	public	WindowsThread
#else
	public	LinuxPThread
#endif
{
public:
	virtual ~myThread() {};
};

