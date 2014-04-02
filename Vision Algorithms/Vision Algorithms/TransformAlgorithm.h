#pragma once
#include "Algorithm.h"
#include <iostream>

class TransformAlgorithm : public Algorithm
{
private:
	double * matrix;
	unsigned int orde;
	bool resize;
	void firstOrderResize(Image& i);
public:
	TransformAlgorithm(double * matrix, unsigned int orde = 0, bool resize = false);
	~TransformAlgorithm();
	virtual void doAlgorithm(Image& i);
	void zeroOrder(Image& i);
	void firstOrder(Image& i);
	int round(double);
	void determineDistanceValue(double * neighbours, double x, double y);
};

