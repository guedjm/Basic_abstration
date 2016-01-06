#ifndef _WIN32

#pragma once

# include "ITCPServer.h"
# include "myTCPSocket.h"
# include "ITCPRemoteClient.h"

class LinuxTCPServer : public ITCPServer
{
public:
	LinuxTCPServer();
	virtual ~LinuxTCPServer();

	virtual int		getReadFd() const;
	virtual bool		readAvailable() const;
	virtual void		readAvailable(bool);

	virtual int		start(std::string const & = "", short = 0, int = 10);
	virtual int		getPort() const;
	virtual void	stop();

	virtual ITCPRemoteClient		*acceptClient();

private:
	bool			_readAvailable;
	myTCPSocket 		_sock;
};
#endif
