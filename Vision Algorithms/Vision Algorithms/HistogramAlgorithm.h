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
	HistogramAlgorithm(char * name, int size);
	~HistogramAlgorithm();
	virtual void doAlgorithm(Image& i);
};