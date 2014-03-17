#pragma once

#include "stdafx.h"

class Algorithm
{
protected:
	char * name;
public:
	const static unsigned char BLUE = 0;
	const static unsigned char GREEN = 1;
	const static unsigned char RED = 2;
	Algorithm(char * name);
	~Algorithm();
	virtual void doAlgorithm(unsigned char * rawData, int bpp, int height, int width, int pitch) = 0;
	char * getName();
};