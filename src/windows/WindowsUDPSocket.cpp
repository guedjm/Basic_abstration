#ifdef _WIN32

#include <string.h>
#include <iostream>
#include <stdio.h>
#include "WindowsTCPSocket.h"
#include "WindowsUDPSocket.h"

WindowsUDPSocket::WindowsUDPSocket()
{
	WindowsTCPSocket::initialize();
	memset(&this->_addr, 0, sizeof(this->_addr));
}

WindowsUDPSocket::~WindowsUDPSocket()
{
}

int		WindowsUDPSocket::init()
{
	this->_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (this->_socket == INVALID_SOCKET)
		return (-1);
	this->_fd = this->_socket;
	return (this->_fd);
}

int		WindowsUDPSocket::closeSock()
{
	return (closesocket(this->_fd));
}

int		WindowsUDPSocket::getReadFd() const
{
	return (this->_socket);
}

unsigned short	WindowsUDPSocket::getPort() const
{
	return (this->_port);
}

int		WindowsUDPSocket::bindSock(std::string const &ip, unsigned short &port)
{
	int	ret;

	this->_addr.sin_family = AF_INET;
	if (ip == "")
		this->_addr.sin_addr.s_addr = INADDR_ANY;
	else
		inet_pton(AF_INET, ip.c_str(), &(this->_addr.sin_addr));
	this->_addr.sin_port = htons(port);
	ret = bind(this->_socket, (struct sockaddr*)(&this->_addr), sizeof(this->_addr));
	if (ret == SOCKET_ERROR)
	{
		printf("Bind failed with error code : %d\n", WSAGetLastError());
		return (-1);
	}
	else
	{
		this->_port = ntohs(this->_addr.sin_port);
		port = this->_port;
	}
	return (ret);
}

int		WindowsUDPSocket::recvFrom(char *buff, int size, std::string &ip, unsigned short &port)
{
	int	ret;
	char b[20];
	int	len = sizeof(this->_addr);

	ret = recvfrom(this->_socket, buff, size, 0, (struct sockaddr*)(&this->_addr), &len);
	if (ret != -1)
	{
		inet_ntop(AF_INET, &this->_addr.sin_addr, b, 20);
		ip = b;
		port = ntohs(this->_addr.sin_port);
	}
	return (ret);
}

int		WindowsUDPSocket::sendTo(const char *buff, int size, std::string const &ip, unsigned short port)
{
	int	ret;

	memset(&this->_addr, 0, sizeof(this->_addr));
	this->_addr.sin_family = AF_INET;
	this->_addr.sin_port = htons(port);
	inet_pton(AF_INET, ip.c_str(), &(this->_addr.sin_addr));
	ret = sendto(this->_socket, buff, size, 0, (struct sockaddr*)(&this->_addr), sizeof(this->_addr));
	return (ret);
}

#endif