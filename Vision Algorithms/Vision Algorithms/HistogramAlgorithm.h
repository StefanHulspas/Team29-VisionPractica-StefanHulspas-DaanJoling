#pragma once
#include "stdafx.h"
#include "Algorithm.h"
#include "Histogram.h"

class HistogramAlgorithm : public Algorithm
{
private:
	int size = 256;
	double * histo;
public:
	//constructor, needs a char * name and a size for the historgram
	HistogramAlgorithm(char * name, int size);
	//destructor.
	~HistogramAlgorithm();
	//the algorithm
	virtual void doAlgorithm(Image& i);
};