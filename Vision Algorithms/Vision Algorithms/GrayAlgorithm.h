#pragma once
#include "stdafx.h"
#include "Algorithm.h"

class GrayAlgorithm : public Algorithm
{
private:
public:
	GrayAlgorithm();
	~GrayAlgorithm();
	virtual void doAlgorithm(Image& i);
};