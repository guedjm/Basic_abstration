#pragma once

class IThread
{
public:
	IThread();
	virtual ~IThread();

	virtual int start(void *(*)(void *), void *) = 0;
	virtual int join() = 0;
	virtual int stop() = 0;
};

