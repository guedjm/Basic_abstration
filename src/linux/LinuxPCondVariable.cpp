#ifndef _WIN32

#include <pthread.h>
#include <stdexcept>
#include "myMutex.h"
#include "LinuxPCondVariable.h"



LinuxPCondVariable::LinuxPCondVariable()
{
	if (pthread_cond_init(&this->_cond, NULL) != 0)
		throw std::runtime_error("Cannot initialize conditionnal variable");
}

LinuxPCondVariable::~LinuxPCondVariable()
{

}

void			LinuxPCondVariable::wait()
{
  if (pthread_cond_wait(&this->_cond, this->_mutex.getMutex()) != 0)
		throw std::runtime_error("Cannot wait on conditional variable");
}

void			LinuxPCondVariable::signal()
{
	if (pthread_cond_signal(&this->_cond) != 0)
		throw std::runtime_error("Cannot emit signal on conditional variable");
}

void			LinuxPCondVariable::broadcast()
{
	if (pthread_cond_broadcast(&this->_cond) != 0)
		throw std::runtime_error("Cannot emit signal on conditional variable");
}

#endif
