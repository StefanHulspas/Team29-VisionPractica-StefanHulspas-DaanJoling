#include "stdafx.h"
#include "EqualizeAlgorithm.h"
#include "HistogramAlgorithm.h"


EqualizeAlgorithm::EqualizeAlgorithm() : Algorithm("Equa_")
{
}


EqualizeAlgorithm::~EqualizeAlgorithm()
{
}

void EqualizeAlgorithm::doAlgorithm(Image& img) {
	unsigned char * rawData = img.getRawData();
	int bpp = img.getBPP();
	int height = img.getHeight();
	int width = img.getWidth();
	int pitch = img.getPitch();

	//step 1
	//Create the histogram
	Histogram h;
	double * histo = h.normalizeHistogram(rawData, bpp, height, width, pitch, size);
	//step 2
	//Modify the histogram for usage
	double * histoModified = new double[size];
	histoModified[0] = histo[0];
	unsigned int x, y;
	for (x = 1; x < size; x++) {
		histoModified[x] = histoModified[x - 1] + histo[x];
	}
	//step 3
	//Change the color values according to the modified histogram
	for (y = 0; y < height; y++) {
		for (x = 0; x < pitch; x += bpp) {
			rawData[y * pitch + x + RED] = histoModified[rawData[y * pitch + x + RED]] * size;
			rawData[y * pitch + x + GREEN] = histoModified[rawData[y * pitch + x + GREEN]] * size;
			rawData[y * pitch + x + BLUE] = histoModified[rawData[y * pitch + x + BLUE]] * size;
		}
	}
}


