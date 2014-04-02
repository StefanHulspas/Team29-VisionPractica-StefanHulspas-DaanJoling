#pragma once
#include "Algorithm.h"
#include <iostream>
class MeanAlgorithm : public Algorithm
{
private:
	int convolutionSize;
public:
	//constructor, the size of the mask is 3.
	MeanAlgorithm(unsigned int convolutionSize = 3);
	// destructor.
	~MeanAlgorithm();
	// this within this methode it will calc the new value of the pixel.
	virtual void doAlgorithm(Image& i);
};

