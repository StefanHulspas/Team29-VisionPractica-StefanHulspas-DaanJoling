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


void HistogramAlgorithm::doAlgorithm(Image& img) {
	unsigned char * rawData = img.getRawData();
	int bpp = img.getBPP();
	int height = img.getHeight();
	int width = img.getWidth();
	int pitch = img.getPitch();
	//Creating the histogram
	Histogram h;
	histo = h.normalizeHistogram(rawData, bpp, height, width, pitch, size);
	//saving the histogram
	h.print(histo, size, name);
}