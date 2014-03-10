#include "stdafx.h"
#include "GrayAlgorithm.h"
#include <iostream>

GrayAlgorithm::GrayAlgorithm()
{
}


GrayAlgorithm::~GrayAlgorithm()
{
}

void GrayAlgorithm::doAlgorithm(Image& i) {
	if (i.getBPP() != 3 && i.getBPP() != 4) {
		std::cout << "Not a valid format for this Algorithm";
	}
	BYTE * pixel = i.getRawData();
	int x, y;
	for (y = 0; y < i.getHeight(); y++) {
		for (x = 0; x < i.getWidth() * i.getBPP(); x += i.getBPP()) {
			int newColor = 0.11 * pixel[y * i.getPitch() + x] + 0.59 * pixel[y * i.getPitch() + x + 1] + 0.3 * pixel[y * i.getPitch() + x + 2];
			pixel[y * i.getPitch() + x] = newColor;
			pixel[y * i.getPitch() + x + 1] = newColor;
			pixel[y * i.getPitch() + x + 2] = newColor;
		}
	}
}


/*
void Image::applyAlgorithm(Algorithm a) {

}*/