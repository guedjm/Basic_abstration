#pragma once

#ifndef _WIN32

#include <pthread.h>
#include <errno.h>
#include "IMutex.h"

class LinuxPMutex : public IMutex
{
protected:
    pthread_mutex_t _mutex;

public:
    LinuxPMutex();
    ~LinuxPMutex();

    void lock();
    void unLock();
    bool tryLock();

    pthread_mutex_t *getMutex();
};

#endif
