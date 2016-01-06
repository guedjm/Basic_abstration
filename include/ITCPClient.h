#pragma once

# include "IReadable.h"
# include "IWritable.h"

class ITCPClient : public IReadable, public IWritable
{
public:
	virtual ~ITCPClient() {}

	virtual int 		getWriteFd() const = 0;
	virtual bool		writeAvailable() const = 0;
	virtual void		writeAvailable(bool) = 0;
	virtual void		prepareData(std::string const &, int) = 0;
	virtual bool 		pendingData() const = 0;
	virtual int			writeData() = 0;


	virtual int 		getReadFd() const = 0;
	virtual bool		readAvailable() const = 0;
	virtual void		readAvailable(bool) = 0;
	virtual int 		readData(std::string &) = 0;

	virtual int 		closeSock() = 0;

	virtual int 		connectTo(std::string const &, short) = 0;
};
