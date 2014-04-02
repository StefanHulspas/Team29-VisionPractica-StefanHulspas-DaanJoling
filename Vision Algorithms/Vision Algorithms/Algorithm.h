#pragma once

#include "stdafx.h"
#include "Image.h"

class Image;

class Algorithm
{
protected:
	//Name of the algorithm
	char * name;
public:
	//Predefined values used in almost all algorithms to
	const static unsigned char BLUE = 0;
	const static unsigned char GREEN = 1;
	const static unsigned char RED = 2;
	//Constructor
	Algorithm(char * name);
	~Algorithm();
	//Main fuction where the algorithm is applied to the picture
	virtual void doAlgorithm(Image& i) = 0;
	//Method to return the name of the algorithm for saving purposes
	char * getName();
};