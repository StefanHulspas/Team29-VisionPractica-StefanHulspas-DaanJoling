#include "stdafx.h"
#include "Algorithm.h"

// constructor, with parameter char * name, its the name of the algorithm.
Algorithm::Algorithm(char * name)
{
	this->name = name;
}
// destructor
Algorithm::~Algorithm()
{
}
// gets the name of the algorithm
char * Algorithm::getName() {
	return name;
}