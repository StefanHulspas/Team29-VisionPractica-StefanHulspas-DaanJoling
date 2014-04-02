#pragma once
#include "Algorithm.h"
class SingleColorAlgorithm : public Algorithm
{
private: 
	unsigned char red = 0;
	unsigned char green = 0;
	unsigned char blue = 0;
public:
	SingleColorAlgorithm(unsigned int color);
	~SingleColorAlgorithm();
	virtual void doAlgorithm(Image& i);
};

