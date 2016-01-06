#pragma once

#include "WindowsMutex.h"
#include "LinuxPMutex.h"

class myMutex :
	#ifdef _WIN32
		public WindowsMutex
	#else
		public LinuxPMutex
	#endif
{
public:
    virtual ~myMutex() {}
};
