#include "stdafx.h"
#include "MeanAlgorithm.h"


MeanAlgorithm::MeanAlgorithm(unsigned int convolutionSize) : Algorithm("Mean_")
{
	if (convolutionSize < 3) convolutionSize = 3;
	else if (convolutionSize % 2 != 1) {
		convolutionSize--;
	}
	this->convolutionSize = convolutionSize;
}


MeanAlgorithm::~MeanAlgorithm()
{
}

void MeanAlgorithm::doAlgorithm(Image& img) {
	unsigned char * rawData = img.getRawData();
	int bpp = img.getBPP();
	int height = img.getHeight();
	int width = img.getWidth();
	int pitch = img.getPitch();
	if (convolutionSize > width) {
		std::cout << "Not a valid format for this Algorithm";
		return;
	}

	int* convolutieRed = new int[convolutionSize * convolutionSize];
	int* convolutieBlue = new int[convolutionSize * convolutionSize];
	int* convolutieGreen = new int[convolutionSize * convolutionSize];
	
	unsigned int x, y, y2, x2;

	unsigned char * originalData = new unsigned char[pitch * height];
	for (y = 0; y < height; y++) {
		for (x = 0; x < pitch; x += bpp) {
			int pixelPlace = y * pitch + x;
			originalData[pixelPlace + RED] = rawData[pixelPlace + RED];
			originalData[pixelPlace + GREEN] = rawData[pixelPlace + GREEN];
			originalData[pixelPlace + BLUE] = rawData[pixelPlace + BLUE];
		}
	}

	for (y = 0; y < height - (convolutionSize - 1); y++) {
		for (x = 0; x < (convolutionSize - 1); x++) {
			for (y2 = 0; y2 < convolutionSize; y2++) {
				int pixelPlace = (y + y2) * pitch + x * bpp;
				int pixelPlaceConvo = y2 + x * convolutionSize;
				convolutieRed[pixelPlaceConvo] = originalData[pixelPlace + RED];
				convolutieGreen[pixelPlaceConvo] = originalData[pixelPlace + GREEN];
				convolutieBlue[pixelPlaceConvo] = originalData[pixelPlace + BLUE];
			}
		}
		int plaats = (convolutionSize - 1) * convolutionSize;
		for (x = 0; x < width * bpp - (convolutionSize - 1) * bpp; x += bpp){
			for (y2 = 0; y2 < convolutionSize; y2++) {
				int pixelPlaats = x + (convolutionSize - 1) * bpp + (y + y2) * pitch;
				convolutieRed[plaats + y2] = originalData[pixelPlaats + RED];
				convolutieGreen[plaats + y2] = originalData[pixelPlaats + GREEN];
				convolutieBlue[plaats + y2] = originalData[pixelPlaats + BLUE];
			}
			plaats += convolutionSize;
			plaats %= convolutionSize * convolutionSize;
			int totalred = 0, totalgreen = 0, totalblue = 0;
			for (y2 = 0; y2 < convolutionSize * convolutionSize; y2++){
				totalred += convolutieRed[y2];
				totalgreen += convolutieGreen[y2];
				totalblue += convolutieBlue[y2];
			}
			int pixelPlaats = x + (convolutionSize - 1) / 2 * bpp + (y + (convolutionSize - 1) / 2) * pitch;
			rawData[pixelPlaats + RED] = totalred / (convolutionSize * convolutionSize);
			rawData[pixelPlaats + GREEN] = totalgreen / (convolutionSize * convolutionSize);
			rawData[pixelPlaats + BLUE] = totalblue / (convolutionSize * convolutionSize);
		}
	}
}