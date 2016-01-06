#pragma once

class IObservable
{
public:
	virtual ~IObservable() {}

	virtual int 		getReadFd() const = 0;
	virtual bool		readAvailable() const = 0;
	virtual void		readAvailable(bool) = 0;
};
