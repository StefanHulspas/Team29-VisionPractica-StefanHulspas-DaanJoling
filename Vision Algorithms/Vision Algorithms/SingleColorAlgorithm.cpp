#include "stdafx.h"
#include "SingleColorAlgorithm.h"


SingleColorAlgorithm::SingleColorAlgorithm(unsigned int color) : Algorithm("")
{
	if (color > 3) color = 3;
	switch (color) {
	case 0: 
		name = "Blue_";
		blue = 1;
		break;
	case 1:
		name = "Green_";
		green = 1;
		break;
	case 2:
		name = "Red_";
		red = 1;
		break;
	}
}


SingleColorAlgorithm::~SingleColorAlgorithm()
{
}

void SingleColorAlgorithm::doAlgorithm(unsigned char * rawData, int bpp, int height, int width, int pitch) {
	unsigned int x, y;
	for (y = 0; y < height; y++) {
		for (x = 0; x < pitch; x += bpp) {
			rawData[y * pitch + x + RED] = rawData[y * pitch + x + RED] * red;
			rawData[y * pitch + x + GREEN] = rawData[y * pitch + x + GREEN] * green;
			rawData[y * pitch + x + BLUE] = rawData[y * pitch + x + BLUE] * blue;
		}
	}
}