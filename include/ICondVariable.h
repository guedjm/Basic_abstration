#pragma once

class ICondVariable
{
public:
	virtual ~ICondVariable() {}

	virtual void wait() = 0;
	virtual void signal() = 0;
	virtual void broadcast() = 0;
};