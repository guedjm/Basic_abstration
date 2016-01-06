#pragma once

# include <string>
# include "IObservable.h"
# include "ITCPRemoteClient.h"

class ITCPServer : public IObservable
{
public:
	virtual ~ITCPServer() {}

	virtual int			getReadFd() const = 0;
	virtual bool		readAvailable() const = 0;
	virtual void		readAvailable(bool) = 0;

	virtual int 		start(std::string const &, short, int) = 0;
	virtual int			getPort() const = 0;
	virtual void		stop() = 0;

	virtual ITCPRemoteClient	*acceptClient() = 0;
};
