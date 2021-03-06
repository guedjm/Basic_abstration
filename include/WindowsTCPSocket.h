#pragma once
#ifdef _WIN32

# include <winsock2.h>
# include <ws2tcpip.h>
# include <windows.h>
# include <stdlib.h>
# include <stdio.h>
# pragma comment(lib, "Ws2_32.lib")

# include "ITCPSocket.h"


class WindowsTCPSocket : public ITCPSocket
{
public:
	WindowsTCPSocket();
	WindowsTCPSocket(struct sockaddr_in &, int);
	virtual ~WindowsTCPSocket();

	virtual int		init();
	virtual int		closeSock();

	virtual int 	getFd() const;

	virtual int		connectTo(std::string const &, short);

	virtual int		bindSock(std::string const & = "", short = 0);
	virtual int		getLocalPort() const;
	virtual int		listenSock(int);
	virtual int 	acceptClient(struct sockaddr_in &);

	virtual int		receive(std::string &);
	virtual int		sendData(std::string const &, int);

	static void			initialize();
	static void			cleanup();
	static std::string	getLastError();

private:
	int 				_fd;
	SOCKET				_clientSocket;
	SOCKADDR_IN		 	_addr;
	struct addrinfo		*_result;
	struct addrinfo		_hints;

	static bool			_initialized;

};

#endif