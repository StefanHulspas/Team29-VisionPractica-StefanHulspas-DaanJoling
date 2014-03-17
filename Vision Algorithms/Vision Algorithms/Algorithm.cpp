#include "stdafx.h"
#include "Algorithm.h"


Algorithm::Algorithm(char * name)
{
	this->name = name;
}

Algorithm::~Algorithm()
{
}

char * Algorithm::getName() {
	return name;
}