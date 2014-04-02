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
	virtual void doAlgorithm(Image& i);
};

