#pragma once

# include <list>
# include <utility>
# include "IObservable.h"
# include "IWritable.h"

class ISelect
{

public:
	virtual ~ISelect() {}
	
	virtual void					addReadFd(IObservable*) = 0;
	virtual void 					addWriteFd(IWritable*) = 0;

	virtual void					removeReadFd(IObservable*) = 0;
	virtual void					removeWriteFd(IWritable*) = 0;

	virtual void					setTimeout(int, int) = 0;
	virtual void					getRemainingTime(int &, int &) const = 0;
	virtual void					getTimeout(int&, int&) const = 0;

	virtual int 					start() = 0;
	virtual std::list<IObservable*>	&getReadyRead() = 0;
	virtual std::list<IWritable*>		&getReadyWrite() = 0;
};
