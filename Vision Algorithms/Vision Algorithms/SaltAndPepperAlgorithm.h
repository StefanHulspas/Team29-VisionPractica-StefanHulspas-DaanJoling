#pragma once
#include "Algorithm.h"
#include <random>
#include <time.h>

class SaltAndPepperAlgorithm : public Algorithm
{
private:
	int percentage;
public:
	//constructor, default value is 10%. changeable in the gui.
	SaltAndPepperAlgorithm(int percentage = 10);
	//destructor
	~SaltAndPepperAlgorithm();
	//algorithm that will randomly set black or white pixels.
	virtual void doAlgorithm(Image& i);
};

