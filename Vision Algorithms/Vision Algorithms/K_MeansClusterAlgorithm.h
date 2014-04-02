#pragma once
#include "Algorithm.h"
#include <iostream>
#include <vector>
#include <string>
#include <time.h>
#include <random>

class K_MeansClusterAlgorithm : public Algorithm
{
private:
	int k;
public:
	//constructor for the k_means, its default is k = 3.
	K_MeansClusterAlgorithm(unsigned int k = 3);
	//destructor
	~K_MeansClusterAlgorithm();
	//the algorithm that will be runned, it needs an Image i.
	void doAlgorithm(Image& i);
};

