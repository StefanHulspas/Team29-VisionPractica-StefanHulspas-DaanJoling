#pragma once
#include "Algorithm.h"
class ThresholdAlgorithm : public Algorithm
{
public:
	//constructor
	ThresholdAlgorithm();
	//destructor
	~ThresholdAlgorithm();
	//algorithm
	void doAlgorithm(Image& i);
};

