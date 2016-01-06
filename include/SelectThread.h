#pragma once

#include "mySelect.h"
#include "myThread.h"
#include "myCondVariable.h"



class SelectThread : public mySelect
{
public:
	SelectThread();
	virtual ~SelectThread();

	void		startThread();
	void		stopThread();
	
	void		startSelect();
	void		selectLoop();

private:
	bool			_stoping;
	myCondVariable	_mainLock;
	myCondVariable	_selectLock;
	myThread		_thread;

};

void			*threadStartup(void *);
