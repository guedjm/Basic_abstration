#pragma once

#include "LinuxPCondVariable.h"
#include "WindowsCondVariable.h"

class myCondVariable :
#ifdef _WIN32
	public WindowsCondVariable
#else
	public LinuxPCondVariable;
#endif
{
public:
		virtual ~myCondVariable() {}
};