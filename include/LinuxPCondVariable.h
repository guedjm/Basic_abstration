#pragma once

#ifndef _WIN32

#include "myMutex.h"
#include "ICondVariable.h"

class LinuxPCondVariable : public ICondVariable
{
public:
	LinuxPCondVariable();
	virtual ~LinuxPCondVariable();

	virtual void wait();
	virtual void signal();
	virtual void broadcast();

private:
	pthread_cond_t	_cond;
	myMutex			_mutex;
};

#endif