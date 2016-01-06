#ifdef _WIN32

#include <stdexcept>
#include "WindowsTCPClient.h"
#include "WindowsTCPSocket.h"

WindowsTCPClient::WindowsTCPClient()
{
	this->_readAvailable = false;
	this->_writeAvailable = false;
	this->_toSendLen = 0;
	this->_sock.init();
}

WindowsTCPClient::~WindowsTCPClient()
{
}

int 			WindowsTCPClient::closeSock()
{
	return (this->_sock.closeSock());
}

int 			WindowsTCPClient::getWriteFd() const
{
	return (this->_sock.getFd());
}

bool			WindowsTCPClient::writeAvailable() const
{
	return (this->_writeAvailable);
}

void			WindowsTCPClient::writeAvailable(bool available)
{
	this->_writeAvailable = available;
}

void 			WindowsTCPClient::prepareData(std::string const &msg, int len)
{
	this->_toSend += msg;
	this->_toSendLen += len;
}

bool			WindowsTCPClient::pendingData() const
{
	return (this->_toSendLen != 0);
}

int 			WindowsTCPClient::writeData()
{
	int 	ret;

	ret = this->_sock.sendData(this->_toSend, this->_toSendLen);
	if (ret != -1 && ret != this->_toSendLen)
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



int 			WindowsTCPClient::getReadFd() const
{
	return (this->_sock.getFd());
}

bool			WindowsTCPClient::readAvailable() const
{
	return (this->_readAvailable);
}

void			WindowsTCPClient::readAvailable(bool available)
{
	this->_readAvailable = available;
}

int 			WindowsTCPClient::readData(std::string &msg)
{
	int 		ret;

	ret = this->_sock.receive(msg);
	this->_readAvailable = false;
	return (ret);
}

int 			WindowsTCPClient::connectTo(std::string const &ip, short port)
{
	int 		ret;

	ret = this->_sock.connectTo(ip, port);
	return (ret);
}


#endif