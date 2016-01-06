#ifndef _WIN32

#include "LinuxPMutex.h"

LinuxPMutex::LinuxPMutex()
{
  pthread_mutex_init(&this->_mutex, NULL);
}

LinuxPMutex::~LinuxPMutex()
{
  pthread_mutex_destroy(&this->_mutex);
}

void			LinuxPMutex::lock()
{
  pthread_mutex_lock(&this->_mutex);
}

void			LinuxPMutex::unLock()
{
  pthread_mutex_unlock(&this->_mutex);
}

bool			LinuxPMutex::tryLock()
{
	return (pthread_mutex_trylock(&this->_mutex) == 0);
}

pthread_mutex_t		*LinuxPMutex::getMutex()
{
  return (&this->_mutex);
}

#endif
