#pragma once
#include "Algorithm.h"
class SingleColorAlgorithm : public Algorithm
{
private: 
	unsigned char red = 0;
	unsigned char green = 0;
	unsigned char blue = 0;
public:
	//constructor, need the color from the gui.
	SingleColorAlgorithm(unsigned int color);
	//destructor
	~SingleColorAlgorithm();
	
	virtual void doAlgorithm(Image& i);
};

