#include "stdafx.h"
#include "HistogramAlgorithm.h"


HistogramAlgorithm::HistogramAlgorithm(char * name, int size) : Algorithm(name)
{
	if (size != 256 && size != 10) size = 256;
	this->size = size;
}

HistogramAlgorithm::~HistogramAlgorithm()
{
	delete[] histo;
}


void HistogramAlgorithm::doAlgorithm(unsigned char * rawData, int bpp, int height, int width, int pitch) {
	Histogram h;
	histo = h.normalizeHistogram(rawData, bpp, height, width, pitch, size);
	h.print(histo, size, name);
}