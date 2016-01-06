#include "SelectThread.h"

SelectThread::SelectThread()
{
	this->_stoping = false;
}

SelectThread::~SelectThread()
{

}

void		SelectThread::startThread()
{
	if (this->_thread.start(&threadStartup, this) == 1)
		throw std::runtime_error("Cannot start thread");
}

void		SelectThread::stopThread()
{
	this->_stoping = true;
}

void		SelectThread::startSelect()
{
	this->_selectLock.signal();
	this->_mainLock.wait();
}

void		SelectThread::selectLoop()
{
	while (!this->_stoping)
	{
		this->start();
		this->_mainLock.signal();
		this->_selectLock.wait();
	}
}
