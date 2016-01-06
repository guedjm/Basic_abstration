#pragma once

# include <string>

class IWritable
{
public:
	static const int 	BUFF_SIZE = 1500;

	virtual ~IWritable() {}

	virtual int			getWriteFd() const = 0;
	virtual bool		writeAvailable() const = 0;
	virtual void		writeAvailable(bool) = 0;

	virtual bool 		pendingData() const = 0;
	virtual void		prepareData(std::string const &, int) = 0;
	virtual int			writeData() = 0;
};
