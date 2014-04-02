#include "stdafx.h"
#include "GrayAlgorithm.h"
#include <iostream>

GrayAlgorithm::GrayAlgorithm() : Algorithm("Gray_")
{
}


GrayAlgorithm::~GrayAlgorithm()
{
}

void GrayAlgorithm::doAlgorithm(Image& img) {
	unsigned char * rawData = img.getRawData();
	int bpp = img.getBPP();
	int height = img.getHeight();
	int width = img.getWidth();
	int pitch = img.getPitch();
	if (bpp != 3 && bpp != 4) {
		std::cout << "Not a valid format for this Algorithm";
		return;
	}
	//combine the red, blue and green values to create the new grey value
	unsigned int x, y;
	for (y = 0; y < height; y++) {
		for (x = 0; x < pitch; x += bpp) {
			int newColor = 0.11 * rawData[y * pitch + x + BLUE] + 0.59 * rawData[y * pitch + x + GREEN] + 0.3 * rawData[y * pitch + x + RED];
			rawData[y * pitch + x + RED] = newColor;
			rawData[y * pitch + x + GREEN] = newColor;
			rawData[y * pitch + x + BLUE] = newColor;
		}
	}
	/*
	Image test(height*2, width*2, bpp, img.getName());
	unsigned char * testrawData = test.getRawData();
	int pitch2 = test.getPitch();
	for (y = 0; y < height; y++) {
		for (x = 0; x < pitch; x += bpp) {
			testrawData[y * pitch2 + x + RED] = rawData[y * pitch + x + RED];
			testrawData[y * pitch2 + x + GREEN] = rawData[y * pitch + x + GREEN];
			testrawData[y * pitch2 + x + BLUE] = rawData[y * pitch + x + BLUE];
		}
	}
	std::string name = test.getName();
	name = "test_" + name;
	std::cout << "saving to test: " << name.c_str() << "\n";
	test.saveImage(name.c_str()); */
}