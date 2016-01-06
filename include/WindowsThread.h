#pragma once

#ifdef _WIN32

#include <Windows.h>
#include "IThread.h"

class WindowsThread : public IThread
{
public:
	WindowsThread();
	virtual ~WindowsThread();

	virtual int start(void *(*)(void *), void *);
	virtual int join();
	virtual int stop();

private:
	HANDLE			_thread;
	DWORD			_id;
};

#endif
