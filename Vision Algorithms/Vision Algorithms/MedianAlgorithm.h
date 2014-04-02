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
	//constructor, the size of the mask is 3.
	MedianAlgorithm(unsigned int convolutionSize = 3);
	//destructor
	~MedianAlgorithm();
	// this within this methode it will calc the new value of the pixel.
	virtual void doAlgorithm(Image& i);
};

