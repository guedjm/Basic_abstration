#pragma once

#ifndef _WIN32

# include <list>
# include <sys/select.h>
# include "ISelect.h"

class LinuxSelect : public ISelect
{
public:
	LinuxSelect();
	virtual ~LinuxSelect();
	
	virtual void						addReadFd(IObservable*);
	virtual void						addWriteFd(IWritable*);

	virtual void						removeReadFd(IObservable*);
	virtual void						removeWriteFd(IWritable*);

	virtual	void						setTimeout(int, int);
	virtual	void 						getRemainingTime(int &, int &) const;
	virtual void						getTimeout(int&, int&) const;

	virtual int							start();
	virtual std::list<IObservable*>	&getReadyRead();
	virtual std::list<IWritable*> 	&getReadyWrite();

private:
	void					setFdSet(fd_set *, fd_set*);
	void		 			getReadyFd(fd_set *, fd_set *);

	bool					_useTimeout;
	int						_maxFd;
	long					_sec;
	long					_usec;
	struct timeval			_timeout;
	std::list<IObservable*>	_readFds;
	std::list<IWritable*>	_writeFds;
	std::list<IObservable*>	_readyRead;
	std::list<IWritable*>	_readyWrite;
};
#endif