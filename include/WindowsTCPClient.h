#pragma once
#ifdef _WIN32

# include "ITCPClient.h"
# include "myTCPSocket.h"

class WindowsTCPClient : public ITCPClient
{
public:
	WindowsTCPClient();
	virtual ~WindowsTCPClient();

	virtual int 		closeSock();

	virtual int 		getWriteFd() const;
	virtual bool		writeAvailable() const;
	virtual void		writeAvailable(bool);
	virtual void		prepareData(std::string const &, int);
	virtual bool 		pendingData() const;
	virtual int			writeData();

	virtual int 		getReadFd() const;
	virtual bool		readAvailable() const;
	virtual void		readAvailable(bool);
	virtual int 		readData(std::string &);

	virtual int 		connectTo(std::string const&, short);

private:
	bool				_readAvailable;
	bool				_writeAvailable;
	int 				_toSendLen;
	std::string 		_toSend;
	myTCPSocket	 		_sock;
};

#endif