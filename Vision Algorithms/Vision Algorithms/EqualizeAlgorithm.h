#pragma once
#include "Algorithm.h"

class EqualizeAlgorithm : public Algorithm
{
private:
	const int size = 256;
public:
	EqualizeAlgorithm();
	~EqualizeAlgorithm();
	virtual void doAlgorithm(unsigned char * rawData, int bpp, int height, int width, int pitch);
};