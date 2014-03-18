#pragma once
#include "Algorithm.h"
#include <iostream>
#include <string>
#include <time.h>
#include <random>
#include <vector>

class K_MeansClusterAlgorithm : public Algorithm
{
private:
	int k;
public:
	K_MeansClusterAlgorithm(unsigned int k = 3);
	~K_MeansClusterAlgorithm();
	void doAlgorithm(unsigned char * rawData, int bpp, int height, int width, int pitch);
};

