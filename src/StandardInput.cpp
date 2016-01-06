# include "StandardInput.h"

StandardInput::StandardInput() : _fd(0)
{
}

StandardInput::~StandardInput()
{
}

int			StandardInput::getReadFd() const
{
	return this->_fd;
}

bool		StandardInput::readAvailable()  const
{
	return (this->_readAvailable);
}

void		StandardInput::readAvailable(bool available)
{
	this->_readAvailable = available;
}