#pragma once

#include <iostream> 
#include <string>
#include <fstream>

class Histogram
{
public:
	static double * normalizeHistogram(unsigned char * rawData, int bpp, int height, int width, int pitch, int size);
	static void print(double * histo, int size, std::string name);
};

