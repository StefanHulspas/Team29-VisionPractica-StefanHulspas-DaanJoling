#pragma once
#include "Algorithm.h"
#include <iostream>
class MeanAlgorithm : public Algorithm
{
private:
	int convolutionSize;
public:
	MeanAlgorithm(unsigned int convolutionSize = 3);
	~MeanAlgorithm();
	virtual void doAlgorithm(unsigned char * rawData, int bpp, int height, int width, int pitch);
};

