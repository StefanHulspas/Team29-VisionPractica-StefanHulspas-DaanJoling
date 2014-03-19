#pragma once
#include "Algorithm.h"
class ThresholdAlgorithm : public Algorithm
{
public:
	ThresholdAlgorithm();
	~ThresholdAlgorithm();
	void doAlgorithm(unsigned char * rawData, int bpp, int height, int width, int pitch);
};

