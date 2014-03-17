#include "stdafx.h"
#include "GrayAlgorithm.h"
#include <iostream>

GrayAlgorithm::GrayAlgorithm() : Algorithm("Gray_")
{
}


GrayAlgorithm::~GrayAlgorithm()
{
}

void GrayAlgorithm::doAlgorithm(unsigned char * rawData, int bpp, int height, int width, int pitch) {
	if (bpp != 3 && bpp != 4) {
		std::cout << "Not a valid format for this Algorithm";
		return;
	}
	unsigned int x, y;
	for (y = 0; y < height; y++) {
		for (x = 0; x < pitch; x += bpp) {
			int newColor = 0.11 * rawData[y * pitch + x + BLUE] + 0.59 * rawData[y * pitch + x + GREEN] + 0.3 * rawData[y * pitch + x + RED];
			rawData[y * pitch + x + RED] = newColor;
			rawData[y * pitch + x + GREEN] = newColor;
			rawData[y * pitch + x + BLUE] = newColor;
		}
	}
}