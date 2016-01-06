#ifdef _WIN32

#include <exception>
#include <iostream>
#include "WindowsTCPSocket.h"
#include "WindowsTCPRemoteClient.h"

WindowsTCPRemoteClient::WindowsTCPRemoteClient(struct sockaddr_in &addr, int fd):
	_sock(addr, fd)
{
	char		buff[50];

	this->_closing = false;
	inet_ntop(AF_INET, &addr.sin_addr, buff, 50);
	this->_ip = buff;
	this->_toSendLen = 0;
}

WindowsTCPRemoteClient::~WindowsTCPRemoteClient()
{
}


std::string const 	&WindowsTCPRemoteClient::getIp() const
{
	return (this->_ip);
}

void				WindowsTCPRemoteClient::prepareClose()
{
	this->_closing = true;
}

bool				WindowsTCPRemoteClient::mustBeClosed() const
{
	return (this->_closing);
}

void				WindowsTCPRemoteClient::closeSock()
{
	this->_sock.closeSock();
}

int 		WindowsTCPRemoteClient::getWriteFd() const
{
	return (this->_sock.getFd());
}

bool		WindowsTCPRemoteClient::writeAvailable() const
{
	return (this->_writeAvailable);
}

void		WindowsTCPRemoteClient::writeAvailable(bool available)
{
	this->_writeAvailable = available;
}

bool 		WindowsTCPRemoteClient::pendingData() const
{
	return (this->_toSendLen != 0);
}


void 		WindowsTCPRemoteClient::prepareData(std::string const &msg, int len)
{
	this->_toSend += msg;
	this->_toSendLen += len;
}

int 		WindowsTCPRemoteClient::writeData()
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



int			WindowsTCPRemoteClient::getReadFd() const
{
	return (this->_sock.getFd());
}

bool		WindowsTCPRemoteClient::readAvailable() const
{
	return (this->_readAvailable);
}

void		WindowsTCPRemoteClient::readAvailable(bool available)
{
	this->_readAvailable = available;
}

int 		WindowsTCPRemoteClient::readData(std::string &data)
{
	int		ret;

	ret = this->_sock.receive(data);
	this->_readAvailable = false;
	return (ret);
}

#endif