#pragma once
#ifndef _WIN32

#include <cerrno>
#include <pthread.h>
#include "IThread.h"

class LinuxPThread : public IThread
{
public:
	LinuxPThread();
	virtual ~LinuxPThread();

	virtual int start(void *(*)(void *), void *);
	virtual int join();
	virtual int stop();

private:
	pthread_t		_thread;
};

#endif
