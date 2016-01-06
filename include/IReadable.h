#pragma once

# include <string>
# include "IObservable.h"

class IReadable : public IObservable
{
public:
	virtual ~IReadable() {}

	virtual int			getReadFd() const = 0;
	virtual bool		readAvailable() const = 0;
	virtual void		readAvailable(bool) = 0;

	virtual int 		readData(std::string &) = 0;

};
