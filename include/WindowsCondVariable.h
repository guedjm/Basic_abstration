#pragma once

#ifdef _WIN32
#include "myMutex.h"
#include "ICondVariable.h"


class WindowsCondVariable : public ICondVariable
{
public:
	WindowsCondVariable();
	virtual ~WindowsCondVariable();

	virtual void wait();
	virtual void signal();
	virtual void broadcast();

private:
	myMutex				_mutex;
	CONDITION_VARIABLE	_cond;
};

#endif