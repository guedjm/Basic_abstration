#pragma once

#include <stdlib.h>
#include <string>
#include <time.h>

#define MIN_CHAR	97
#define MAX_CHAR	122

class	RandomGenerator
{

public:

	void	init()const;
	int		generateNumber(int, int)const;
	void  generateString(std::string &, int)const;

	RandomGenerator();
	~RandomGenerator();
};
