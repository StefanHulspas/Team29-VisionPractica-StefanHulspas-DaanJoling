#pragma once
#include "Algorithm.h"
#include <random>
#include <time.h>

class SaltAndPepperAlgorithm : public Algorithm
{
private:
	int percentage;
public:
	SaltAndPepperAlgorithm(int percentage = 10);
	~SaltAndPepperAlgorithm();
	virtual void doAlgorithm(unsigned char * rawData, int bpp, int height, int width, int pitch);
};

