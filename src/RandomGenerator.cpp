#include "RandomGenerator.h"

void	RandomGenerator::init() const
{
	srand(static_cast<unsigned int>(time(0)));
}

int		RandomGenerator::generateNumber(int min, int max) const
{
	return ((rand() % (max - min)) + min);
}

void RandomGenerator::generateString(std::string & s, int length) const{

	for (int i = 0; i < length; i++){
		s += this->generateNumber(MIN_CHAR, MAX_CHAR);
	}
}

RandomGenerator::RandomGenerator()
{
}

RandomGenerator::~RandomGenerator()
{
}