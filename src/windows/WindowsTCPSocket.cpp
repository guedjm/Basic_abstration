#ifdef _WIN32

#include <strsafe.h>

#include "WindowsTCPSocket.h"

bool WindowsTCPSocket::_initialized = false;

void		WindowsTCPSocket::initialize()
{
	if (WindowsTCPSocket::_initialized == false)
	{
		WindowsTCPSocket::_initialized = true;
		WSADATA wsaData;
		int ret = WSAStartup(MAKEWORD(2, 2), &wsaData);
		if (ret != 0)
			throw std::runtime_error("WSAStartup failed");
	}
}

void		WindowsTCPSocket::cleanup()
{
	if (WindowsTCPSocket::_initialized == true)
	{
		WindowsTCPSocket::_initialized = false;
		int ret = WSACleanup();
		if (ret != 0)
			throw std::runtime_error("WSACleanup failed: " + WindowsTCPSocket::getLastError());
	}
}

std::string	WindowsTCPSocket::getLastError()
{
	LPVOID lpMsgBuf;
	DWORD dw = WSAGetLastError();

	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		dw,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf,
		0, NULL);

	char* tmp = (char*)lpMsgBuf;
	std::string r(tmp);
	LocalFree(lpMsgBuf);
	return r;
}


WindowsTCPSocket::WindowsTCPSocket()
{
	WindowsTCPSocket::initialize();
	memset(&this->_addr, 0, sizeof(this->_addr));
	this->_result = NULL;
	this->_clientSocket = INVALID_SOCKET;
}

WindowsTCPSocket::WindowsTCPSocket(struct sockaddr_in &addr, int fd)
{
	this->_fd = fd;
	this->_clientSocket = fd;
	memcpy(&this->_addr, &addr, sizeof(addr));
}

WindowsTCPSocket::~WindowsTCPSocket()
{
}

int			WindowsTCPSocket::init()
{
	ZeroMemory(&this->_hints, sizeof(this->_hints));
	this->_hints.ai_family = AF_INET;
	this->_hints.ai_socktype = SOCK_STREAM;
	this->_hints.ai_protocol = IPPROTO_TCP;
	this->_hints.ai_flags = AI_PASSIVE;

	this->_clientSocket = socket(this->_hints.ai_family, this->_hints.ai_socktype, this->_hints.ai_protocol);
	if (this->_clientSocket == INVALID_SOCKET)
		this->_clientSocket = -1;
	else
		this->_fd = this->_clientSocket;
	return (this->_clientSocket);
}

int 		WindowsTCPSocket::closeSock()
{
	int ret = closesocket(this->_clientSocket);
	return (ret == 0 ? -1 : 0);
}

int 		WindowsTCPSocket::getFd() const
{
	return (this->_fd);
}

int 					WindowsTCPSocket::connectTo(std::string const &ip, short port)
{
	int 				ret;

	this->_addr.sin_family = AF_INET;
	this->_addr.sin_port = htons(port);
	inet_pton(AF_INET, ip.c_str(), &(this->_addr.sin_addr));
	ret = connect(this->_clientSocket, (sockaddr *)(&this->_addr), sizeof(this->_addr));

	return (ret);
}

int 					WindowsTCPSocket::bindSock(std::string const &ip, short port)
{
	int iResult;

	this->_addr.sin_family = AF_INET;
	if (ip == "")
		this->_addr.sin_addr.s_addr = INADDR_ANY;
	else
		inet_pton(AF_INET, ip.c_str(), &(this->_addr.sin_addr));
	if (port != 0)
		this->_addr.sin_port = htons(port);
	iResult = bind(this->_clientSocket, (sockaddr *)(&this->_addr), sizeof(this->_addr));
	return (iResult);
}

int					WindowsTCPSocket::getLocalPort() const
{
	int				size = sizeof(this->_addr);

	if (getsockname(this->_clientSocket, (struct sockaddr *)&this->_addr, &size) == -1)
		perror("getsockname");
	return (ntohs(this->_addr.sin_port));
}

int 					WindowsTCPSocket::listenSock(int backlog)
{
	int 				ret;

	ret = listen(this->_clientSocket, backlog);
	return (ret);
}

int 					WindowsTCPSocket::acceptClient(struct sockaddr_in &addr_in)
{
	int					remoteFd;

	socklen_t in_len = sizeof(addr_in);
	remoteFd = accept(this->_clientSocket, (sockaddr *)&addr_in, &in_len);
	return (remoteFd == INVALID_SOCKET ? -1 : remoteFd);
}

int 				WindowsTCPSocket::receive(std::string &buff)
{
	int 			i;
	int 			totalSize;
	char			tmp[1500];

	totalSize = 0;
	while (totalSize == 0 || i == 1500)
	{
		i = recv(this->_clientSocket, tmp, 1500, 0);
		if (i <= 0)
			return (i);
		buff.append(tmp, i);
		totalSize += i;
	}
	return (totalSize);
}

int 				WindowsTCPSocket::sendData(std::string const &buff, int len)
{
	int				iSendResult;

 	iSendResult = send(this->_clientSocket, buff.c_str(), len, 0);
	return (iSendResult == SOCKET_ERROR ? -1 : iSendResult);
}

#endif