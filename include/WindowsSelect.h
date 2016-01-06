#pragma once

#ifdef _WIN32


# include <list>
# include <winsock2.h>
# include <ws2tcpip.h>
# include <windows.h>


# include "ISelect.h"

# define SEC_IN_USEC				(1000000)

class WindowsSelect : public ISelect
{
public:
	WindowsSelect();
	virtual ~WindowsSelect();

	virtual void	addReadFd(IObservable*);
	virtual void	addWriteFd(IWritable*);

	virtual void	removeReadFd(IObservable*);
	virtual void	removeWriteFd(IWritable*);

	virtual	void	setTimeout(int, int);
	virtual	void 	getRemainingTime(int&, int&) const;
	virtual void	getTimeout(int&, int&) const;

	virtual int		start();

	virtual std::list<IObservable*>	&getReadyRead();
	virtual std::list<IWritable*> 	&getReadyWrite();


private:
	void					setFdSet(fd_set*, fd_set*);
	void		 			getReadyFd(fd_set*, fd_set*);

	void					getTime();
	void					updateTimeout(bool);

	bool					keyWasPressed() const;

	IObservable*			_stdin;
	bool					_useTimeout;
	unsigned long long int	_time;
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