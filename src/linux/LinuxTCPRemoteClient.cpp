#ifndef _WIN32

#include <stdexcept>
#include <exception>
#include <iostream>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "LinuxTCPRemoteClient.h"

LinuxTCPRemoteClient::LinuxTCPRemoteClient(struct sockaddr_in &addr,
					   int fd):
  _sock(addr, fd)
{
	this->_readAvailable = false;
	this->_writeAvailable = false;
	this->_closing = false;
	this->_ip = inet_ntoa(addr.sin_addr);
	this->_toSendLen = 0;
}

LinuxTCPRemoteClient::~LinuxTCPRemoteClient()
{
}

int 		LinuxTCPRemoteClient::getWriteFd() const
{
	return (this->_sock.getFd());
}

bool		LinuxTCPRemoteClient::writeAvailable() const
{
	return (this->_writeAvailable);
}

void		LinuxTCPRemoteClient::writeAvailable(bool available)
{
	this->_writeAvailable = available;
}

bool 		LinuxTCPRemoteClient::pendingData() const
{
	return (this->_toSendLen != 0);
}

void 		LinuxTCPRemoteClient::prepareData(std::string const& msg, int len)
{
	this->_toSend += msg;
	this->_toSendLen += len;
}

int 		LinuxTCPRemoteClient::writeData()
{
	int 	ret;

	ret = this->_sock.sendData(this->_toSend, this->_toSendLen);
	if (ret != this->_toSendLen)
	{
		this->_toSend = this->_toSend.substr(ret);
		this->_toSendLen -= ret;
	}
	else
	{
		this->_toSend.clear();
		this->_toSendLen = 0;
	}
	this->_writeAvailable = false;
	return (ret);
}



int			LinuxTCPRemoteClient::getReadFd() const
{
	return (this->_sock.getFd());
}

bool			LinuxTCPRemoteClient::readAvailable() const
{
	return (this->_readAvailable);
}

void			LinuxTCPRemoteClient::readAvailable(bool available)
{
	this->_readAvailable = available;
}

int	 		LinuxTCPRemoteClient::readData(std::string &data)
{
	int		ret;

	ret = this->_sock.receive(data);
	this->_readAvailable = false;
	return (ret);
}




std::string const 	&LinuxTCPRemoteClient::getIp() const
{
	return (this->_ip);
}

void				LinuxTCPRemoteClient::prepareClose()
{
	this->_closing = true;
}

bool				LinuxTCPRemoteClient::mustBeClosed() const
{
	return (this->_closing);
}

void				LinuxTCPRemoteClient::closeSock()
{
	this->_sock.closeSock(); 
}


#endif
