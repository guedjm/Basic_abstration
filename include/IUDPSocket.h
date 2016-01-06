#pragma once

#include <string>
#include "IObservable.h"

class IUDPSocket : public IObservable
{
public:
	virtual ~IUDPSocket() {}

	virtual int		init() = 0;

	virtual int		getReadFd() const = 0;

	virtual unsigned short	getPort() const = 0;

	virtual int		bindSock(std::string const &, unsigned short &) = 0;
	virtual int		closeSock() = 0;

	virtual int		recvFrom(char *, int, std::string &, unsigned short &) = 0;
	virtual int		sendTo(const char *, int, std::string const &, unsigned short) = 0;

};
