#pragma once
#include "Algorithm.h"
#include <iostream>
class MedianAlgorithm : public Algorithm
{
private:
	int convolutionSize;
	int * sortArray(const int *); 
	int partition(int* input, int p, int r);
	void quicksort(int* input, int p, int r);
public:
	MedianAlgorithm(unsigned int convolutionSize = 3);
	~MedianAlgorithm();
	virtual void doAlgorithm(Image& i);
};

