#ifndef _WIN32

#include <stdexcept>
#include "LinuxTCPClient.h"
#include "LinuxTCPSocket.h"

LinuxTCPClient::LinuxTCPClient()
{
	this->_toSendLen = 0;
	this->_writeAvailable = false;
	this->_readAvailable = false;
	this->_sock.init();
}

LinuxTCPClient::~LinuxTCPClient()
{
}

int 			LinuxTCPClient::closeSock()
{
	return (this->_sock.closeSock());
}

int 			LinuxTCPClient::getWriteFd() const
{
	return (this->_sock.getFd());
}

bool			LinuxTCPClient::writeAvailable() const
{
	return (this->_writeAvailable);
}

void			LinuxTCPClient::writeAvailable(bool available)
{
	this->_writeAvailable = available;
}

void			LinuxTCPClient::prepareData(std::string const &data, int len)
{
	this->_toSendLen += len;
	this->_toSend += data;
}

bool			LinuxTCPClient::pendingData() const
{
	return (this->_toSendLen != 0);
}

int				LinuxTCPClient::writeData()
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


int 			LinuxTCPClient::getReadFd() const
{
	return (this->_sock.getFd());
}

bool			LinuxTCPClient::readAvailable() const
{
	return (this->_readAvailable);
}

void			LinuxTCPClient::readAvailable(bool available)
{
	this->_readAvailable = available;
}

int 			LinuxTCPClient::readData(std::string &msg)
{
	int 		ret;

	ret = this->_sock.receive(msg);
	this->_readAvailable = false;
	return (ret);
}

int 			LinuxTCPClient::connectTo(std::string const &ip, short port)
{
	int 		ret;

	ret = this->_sock.connectTo(ip, port);
	return (ret);
}


#endif
