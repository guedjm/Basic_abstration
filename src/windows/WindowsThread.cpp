#ifdef _WIN32

#include "WindowsThread.h"

WindowsThread::WindowsThread()
{
}

WindowsThread::~WindowsThread()
{
}

int			WindowsThread::start(void *(*ptr)(void *), void *arg)
{
	this->_thread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ptr, arg, 0, &_id);
	if (this->_thread != NULL)
		return (0);
	return (-1);
}

int			WindowsThread::join()
{
	if (WaitForSingleObject(this->_thread, INFINITE) == -1)
		return (-1);
	return (0);
}

int			WindowsThread::stop()
{
	if (TerminateThread(this->_thread, this->_id) != 0)
		return (0);
	return (1);
}

#endif