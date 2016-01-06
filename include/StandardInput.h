#pragma once

# include "IReadable.h"

class StandardInput : public IObservable
{
public:
	StandardInput();
	virtual ~StandardInput();

	virtual int			getReadFd() const;
	virtual bool		readAvailable() const;
	virtual void		readAvailable(bool);

private:
	int	const			_fd;
	bool				_readAvailable;
};
