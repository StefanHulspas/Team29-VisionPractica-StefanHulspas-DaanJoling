#include "stdafx.h"
#include "SaltAndPepperAlgorithm.h"


SaltAndPepperAlgorithm::SaltAndPepperAlgorithm(int percentage) : Algorithm("salt&pepper_")
{
	if (percentage >= 0 && percentage <= 100) this->percentage = percentage;
}


SaltAndPepperAlgorithm::~SaltAndPepperAlgorithm()
{
}


void SaltAndPepperAlgorithm::doAlgorithm(unsigned char * rawData, int bpp, int height, int width, int pitch) {
	srand(time(NULL));
	double random = 0;
	unsigned int x, y;
	for (y = 0; y < height; y++) {
		for (x = 0; x < pitch; x += bpp) {
			random = (double)rand() / (double)RAND_MAX; 
			if (random < (double)percentage / (double)100 / 2) {
				rawData[y * pitch + x + RED] = 0;
				rawData[y * pitch + x + GREEN] = 0;
				rawData[y * pitch + x + BLUE] = 0;
			}
			else if (random < (double)percentage / (double)100) {
				rawData[y * pitch + x + RED] = 255;
				rawData[y * pitch + x + GREEN] = 255;
				rawData[y * pitch + x + BLUE] = 255;
			}
		}
	}
}
