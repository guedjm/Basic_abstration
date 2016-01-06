#pragma once
#ifdef _WIN32

# include "ITCPServer.h"
# include "myTCPSocket.h"
# include "ITCPRemoteClient.h"

class WindowsTCPServer : public ITCPServer
{
public:
	WindowsTCPServer();
	virtual ~WindowsTCPServer();

	virtual int		getReadFd() const;
	virtual bool	readAvailable() const;
	virtual void	readAvailable(bool);

	virtual int		start(std::string const& = "", short = 0, int = 10);
	virtual int		getPort() const;
	virtual void	stop();

	virtual ITCPRemoteClient		*acceptClient();

private:
	bool			_readAvailable;
	myTCPSocket 	_sock;
};

#endif