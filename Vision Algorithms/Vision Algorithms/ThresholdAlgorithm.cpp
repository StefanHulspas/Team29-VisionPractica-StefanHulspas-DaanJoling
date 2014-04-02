#include "stdafx.h"
#include "ThresholdAlgorithm.h"


ThresholdAlgorithm::ThresholdAlgorithm() : Algorithm("Threshold_")
{
}


ThresholdAlgorithm::~ThresholdAlgorithm()
{
}


void ThresholdAlgorithm::doAlgorithm(Image& img) {
	unsigned char * rawData = img.getRawData();
	int bpp = img.getBPP();
	int height = img.getHeight();
	int width = img.getWidth();
	int pitch = img.getPitch();
	int lower = 0, higher = 0, tOld = 0, tNew = 0, higherCount = width * height, lowerCount = 4;
	unsigned int x, y;
	for (y = 0; y < height; y++) {
		for (x = 0; x < pitch; x += bpp) {
			higher += rawData[y * pitch + x + BLUE];
		}
	}
	tNew = (lower / lowerCount + higher / higherCount) / 2;
	while (tOld != tNew) {
		higherCount = lowerCount = higher = lower = 0;
		for (y = 0; y < height; y++) {
			for (x = 0; x < pitch; x += bpp) {
				if (rawData[y * pitch + x + BLUE] < tNew) {
					lower += rawData[y * pitch + x + BLUE];
					lowerCount++;
				}
				else {
					higher += rawData[y * pitch + x + BLUE];
					higherCount++;
				}
			}
		}
		tOld = tNew;
		tNew = (lower / lowerCount + higher / higherCount) / 2;
	}
	for (y = 0; y < height; y++) {
		for (x = 0; x < pitch; x += bpp) {
			if (rawData[y * pitch + x + BLUE] >= tNew) {
				rawData[y * pitch + x + RED] = 255;
				rawData[y * pitch + x + GREEN] = 255;
				rawData[y * pitch + x + BLUE] = 255;
			}
			else {
				rawData[y * pitch + x + RED] = 0;
				rawData[y * pitch + x + GREEN] = 0;
				rawData[y * pitch + x + BLUE] = 0;
			}
		}
	}
}