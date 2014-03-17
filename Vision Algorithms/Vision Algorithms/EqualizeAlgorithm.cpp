#include "stdafx.h"
#include "EqualizeAlgorithm.h"
#include "HistogramAlgorithm.h"


EqualizeAlgorithm::EqualizeAlgorithm() : Algorithm("Equa_")
{
}


EqualizeAlgorithm::~EqualizeAlgorithm()
{
}

void EqualizeAlgorithm::doAlgorithm(unsigned char * rawData, int bpp, int height, int width, int pitch) {
	Histogram h;
	double * histo = h.normalizeHistogram(rawData, bpp, height, width, pitch, size);
	double * histoModified = new double[size];
	histoModified[0] = histo[0];
	unsigned int x, y;
	for (x = 1; x < size; x++) {
		histoModified[x] = histoModified[x - 1] + histo[x];
	}
	for (y = 0; y < height; y++) {
		for (x = 0; x < pitch; x += bpp) {
			rawData[y * pitch + x + RED] = histoModified[rawData[y * pitch + x + RED]] * size;
			rawData[y * pitch + x + GREEN] = histoModified[rawData[y * pitch + x + GREEN]] * size;
			rawData[y * pitch + x + BLUE] = histoModified[rawData[y * pitch + x + BLUE]] * size;
		}
	}
}


