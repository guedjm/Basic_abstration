#ifndef _WIN32

#include <stdexcept>
#include <exception>
#include <iostream>
#include <algorithm>
#include "LinuxSelect.h"

LinuxSelect::LinuxSelect()
{
	this->_useTimeout = false;
	this->_maxFd = 0;
	this->_sec = 0;
	this->_usec = 0;
}

LinuxSelect::~LinuxSelect()
{
}

void			LinuxSelect::addReadFd(IObservable *fd)
{
	if (std::find(this->_readFds.begin(), this->_readFds.end(), fd) == this->_readFds.end())
		this->_readFds.push_back(fd);
}

void			LinuxSelect::addWriteFd(IWritable *fd)
{
	if (std::find(this->_writeFds.begin(), this->_writeFds.end(), fd) == this->_writeFds.end())
		this->_writeFds.push_back(fd);	
}

void			LinuxSelect::removeReadFd(IObservable *fd)
{
	std::list<IObservable*>::iterator it = std::find(this->_readFds.begin(), this->_readFds.end(), fd);

	if (it != this->_readFds.end())
		this->_readFds.erase(it);
}

void			LinuxSelect::removeWriteFd(IWritable *fd)
{
	std::list<IWritable*>::iterator it = std::find(this->_writeFds.begin(), this->_writeFds.end(), fd);

	if (it != this->_writeFds.end())
		this->_writeFds.erase(it);
}

void			LinuxSelect::setTimeout(int sec, int usec)
{
	if (sec == -1 || usec == -1)
		this->_useTimeout = false;
	else
	{
		this->_useTimeout = true;
		this->_sec = sec;
		this->_usec = usec;
	}
}

void			LinuxSelect::getRemainingTime(int &sec, int &usec) const
{
	sec = this->_timeout.tv_sec;
	usec = this->_timeout.tv_usec;
}

void			LinuxSelect::getTimeout(int &sec, int &usec) const
{
	sec = this->_sec;
	usec = this->_usec;
}

std::list<IObservable*>	&LinuxSelect::getReadyRead()
{
	return (this->_readyRead);
}

std::list<IWritable*>	&LinuxSelect::getReadyWrite()
{
	return (this->_readyWrite);
}

int				LinuxSelect::start()
{
	int				ret;
	fd_set			readFds;
	fd_set 			writeFds;

	this->_maxFd = 0;
	FD_ZERO(&readFds);
	FD_ZERO(&writeFds);
	this->_readyRead.clear();
	this->_readyWrite.clear();
	this->_timeout.tv_sec = this->_sec;
	this->_timeout.tv_usec = this->_usec;
	this->setFdSet(&readFds, &writeFds);
	ret = select(this->_maxFd + 1, &readFds, &writeFds, 0,
				(this->_useTimeout) ? &this->_timeout : 0);
	if (ret > 0)
		this->getReadyFd(&readFds, &writeFds);
	else if (ret == -1)
		throw std::runtime_error("Select failed");
	return (ret);
}

void					LinuxSelect::setFdSet(fd_set *readFds, fd_set *writeFds)
{
	int					fd;

	for (std::list<IObservable*>::iterator it = this->_readFds.begin();
		it != this->_readFds.end(); ++it)
		{
			fd = ((*it)->getReadFd());
			FD_SET(fd, readFds);
			if (fd > this->_maxFd)
				this->_maxFd = fd;
		}
	for (std::list<IWritable*>::iterator it = this->_writeFds.begin();
		it != this->_writeFds.end(); ++it)
		{
			fd = ((*it)->getWriteFd());
			FD_SET(fd, writeFds);
			if (fd > this->_maxFd)
				this->_maxFd = fd;
		}
}

void					LinuxSelect::getReadyFd(fd_set *readFds, 
												fd_set *writeFds)
{
	for (std::list<IObservable*>::iterator it = this->_readFds.begin();
			it != this->_readFds.end(); ++it)
		{
			if (FD_ISSET((*it)->getReadFd(), readFds))
			{
				(*it)->readAvailable(true);
				this->_readyRead.push_back(*it);
			}
		}
	for (std::list<IWritable*>::iterator it = this->_writeFds.begin();
			it != this->_writeFds.end(); ++it)
		{
			if (FD_ISSET((*it)->getWriteFd(), writeFds))
			{
				(*it)->writeAvailable(true);
				this->_readyWrite.push_back(*it);
			}
		}
}
#endif
