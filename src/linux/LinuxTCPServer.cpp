#ifndef _WIN32

#include <stdexcept>
#include "myTCPRemoteClient.h"
#include "LinuxTCPServer.h"
#include "LinuxTCPSocket.h"
#include "LinuxTCPRemoteClient.h"

LinuxTCPServer::LinuxTCPServer()
{
  this->_readAvailable = false;
  this->_sock.init();
}

LinuxTCPServer::~LinuxTCPServer()
{
}

int 			LinuxTCPServer::getReadFd() const
{
	return (this->_sock.getFd());
}

bool			LinuxTCPServer::readAvailable() const
{
  return (this->_readAvailable);
}

void			LinuxTCPServer::readAvailable(bool available)
{
  this->_readAvailable = available;
}

int 			LinuxTCPServer::start(std::string const &ip,
	short port, int backlog)
{
	int 		ret;

	ret = this->_sock.bindSock(ip, port);
	if (ret != -1)
		ret = this->_sock.listenSock(backlog);
	return (ret);
}

int			LinuxTCPServer::getPort() const
{
  return (this->_sock.getLocalPort());
}

void			LinuxTCPServer::stop()
{
	this->_sock.closeSock();
}

ITCPRemoteClient		*LinuxTCPServer::acceptClient()
{
	int 				ret;
	struct sockaddr_in	addr;
	ITCPRemoteClient 		*newClient;


	ret = this->_sock.acceptClient(addr);
	if (ret == -1)
	  return (NULL);
	newClient = new myTCPRemoteClient(addr, ret);
	if (newClient == 0)
		throw std::runtime_error("Allocation failed");
	this->_readAvailable = false;
	return (newClient);
}
#endif
