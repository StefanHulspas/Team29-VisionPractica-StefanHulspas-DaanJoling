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
	//transforAlgorithm, paramters: the matrix, how much orde, and a boolean resize.
	TransformAlgorithm(double * matrix, unsigned int orde = 0, bool resize = false);
	// destructor
	~TransformAlgorithm();
	//the do algorithm
	virtual void doAlgorithm(Image& i);
	//zero Order algorithm
	void zeroOrder(Image& i);
	//first orde algorithm
	void firstOrder(Image& i);
	int round(double);
	void determineDistanceValue(double * neighbours, double x, double y);
};

