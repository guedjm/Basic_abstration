#ifdef _WIN32

#include <exception>
#include "WindowsTCPServer.h"
#include "WindowsTCPSocket.h"
#include "myTCPRemoteClient.h"
#include "WindowsTCPRemoteClient.h"

WindowsTCPServer::WindowsTCPServer()
{
	this->_sock.init();
}

WindowsTCPServer::~WindowsTCPServer()
{
}

int 			WindowsTCPServer::getReadFd() const
{
	return (this->_sock.getFd());
}

bool			WindowsTCPServer::readAvailable() const
{
	return (this->_readAvailable);
}

void			WindowsTCPServer::readAvailable(bool available)
{
	this->_readAvailable = available;
}

int 			WindowsTCPServer::start(std::string const &ip,
	short port, int backlog)
{
	int 		ret;

	ret = this->_sock.bindSock(ip, port);
	if (ret != -1)
		ret = this->_sock.listenSock(backlog);
	return (ret);
}

int				WindowsTCPServer::getPort() const
{
	return (this->_sock.getLocalPort());
}

void			WindowsTCPServer::stop()
{
	this->_sock.closeSock();
}

ITCPRemoteClient		*WindowsTCPServer::acceptClient()
{
	int 				ret;
	struct sockaddr_in	addr;
	ITCPRemoteClient 		*newClient;


	ret = this->_sock.acceptClient(addr);
	if (ret == -1)
		return (NULL);
	newClient = new myTCPRemoteClient(addr, ret);
	if (newClient == 0)
		throw std::runtime_error("WindowsTCPServer: Allocation failed");
	this->_readAvailable = false;
	return (newClient);
}

#endif