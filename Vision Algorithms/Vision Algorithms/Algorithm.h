#pragma once

#include "stdafx.h"
#include "Image.h"
#include <iostream>

class Algorithm
{
protected:
	const int BLUE = 0;
	const int GREEN = 1;
	const int RED = 2;
	~Algorithm();
public:
	Algorithm();
	Algorithm(const Algorithm& a);
	void virtual doAlgorithm(Image i);
};