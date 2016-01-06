#include <stdexcept>
#include "WindowsCondVariable.h"

#ifdef _WIN32

WindowsCondVariable::WindowsCondVariable()
{
	InitializeConditionVariable(&this->_cond);
}

WindowsCondVariable::~WindowsCondVariable()
{
}

void			WindowsCondVariable::wait()
{
	if (SleepConditionVariableCS(&this->_cond, this->_mutex.getMutex(), INFINITE) != 0)
		throw std::runtime_error("Cannot wait on cond variable");
}

void			WindowsCondVariable::signal()
{
	WakeConditionVariable(&this->_cond);
}

void			WindowsCondVariable::broadcast()
{
	WakeAllConditionVariable(&this->_cond);
}

#endif