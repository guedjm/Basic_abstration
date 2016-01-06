#pragma once

# include "IWritable.h"
# include "IReadable.h"

class ITCPRemoteClient : public IWritable, public IReadable
{
public:
	virtual ~ITCPRemoteClient() {}

	virtual int 				getWriteFd() const = 0;
	virtual bool				writeAvailable() const = 0;
	virtual void				writeAvailable(bool) = 0;
	virtual bool				pendingData() const = 0;
	virtual void				prepareData(std::string const &, int) = 0;
	virtual int					writeData() = 0;

	virtual int 				getReadFd() const = 0;
	virtual bool				readAvailable() const = 0;
	virtual void				readAvailable(bool) = 0;
	virtual int 				readData(std::string &) = 0;


	virtual std::string const	&getIp() const = 0;

	virtual void				prepareClose() = 0;
	virtual bool 				mustBeClosed() const = 0;
	virtual void				closeSock() = 0;
};
