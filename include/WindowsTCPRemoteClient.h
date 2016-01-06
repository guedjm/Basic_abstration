#pragma once
#ifdef _WIN32

# include <winsock2.h>
# include <ws2tcpip.h>
# include <windows.h>

# include "myTCPSocket.h"
# include "ITCPRemoteClient.h"

class WindowsTCPRemoteClient : public ITCPRemoteClient
{
public:
	WindowsTCPRemoteClient(struct sockaddr_in &, int fd);
	virtual ~WindowsTCPRemoteClient();

	virtual int 				getWriteFd() const;
	virtual bool				writeAvailable() const;
	virtual void				writeAvailable(bool);
	virtual bool				pendingData() const;
	virtual void				prepareData(std::string const &, int);
	virtual int					writeData();

	virtual int 				getReadFd() const;
	virtual bool				readAvailable() const;
	virtual void				readAvailable(bool);
	virtual int 				readData(std::string &);

	virtual std::string const&	getIp() const;

	virtual void				prepareClose();
	virtual bool 				mustBeClosed() const;
	virtual void				closeSock();

private:
	bool				_readAvailable;
	bool				_writeAvailable;
	bool				_closing;
	std::string 		_ip;
	myTCPSocket			_sock;
	int 				_toSendLen;
	std::string 		_toSend;
};

#endif