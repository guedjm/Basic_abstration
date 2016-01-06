#ifndef _WIN32

#include "LinuxPThread.h"

LinuxPThread::LinuxPThread()
{
}

LinuxPThread::~LinuxPThread()
{
}

int			LinuxPThread::start(void *(*ptr)(void *), void *arg)
{
	return (pthread_create(&this->_thread, NULL, ptr, arg));
}

int			LinuxPThread::join()
{
	return (pthread_join(this->_thread, NULL));
}

int			LinuxPThread::stop()
{
       pthread_exit(&this->_thread);
	   return (0);
}

#endif
