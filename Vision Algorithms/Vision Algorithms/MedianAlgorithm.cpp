#include "stdafx.h"
#include "MedianAlgorithm.h"


MedianAlgorithm::MedianAlgorithm(unsigned int convolutionSize) : Algorithm("Median_")
{
	if (convolutionSize < 3) convolutionSize = 3;
	else if (convolutionSize % 2 != 1) {
		convolutionSize--;
	}
	this->convolutionSize = convolutionSize;
}


MedianAlgorithm::~MedianAlgorithm()
{
}

void MedianAlgorithm::doAlgorithm(unsigned char * rawData, int bpp, int height, int width, int pitch) {
	if (convolutionSize > width || convolutionSize > height) {
		std::cout << "Not a valid format for this Algorithm.\nFilter is bigger then the image.\nNothing is done.\n";
		return;
	}

	int* convolutieRed = new int[convolutionSize * convolutionSize];
	int* convolutieBlue = new int[convolutionSize * convolutionSize];
	int* convolutieGreen = new int[convolutionSize * convolutionSize];

	unsigned int x, y, y2, x2;

	unsigned char * originalData = new unsigned char[width * bpp * height];
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
			int * sortedConvolutieRed = sortArray(convolutieRed);
			int * sortedConvolutieGreen = sortArray(convolutieGreen);
			int * sortedConvolutieBlue = sortArray(convolutieBlue);
			int pixelPlaats = x + (convolutionSize - 1) / 2 * bpp + (y + (convolutionSize - 1) / 2) * pitch;
			int convoMid = convolutionSize * convolutionSize / 2;
			rawData[pixelPlaats + RED] = sortedConvolutieRed[convoMid];
			rawData[pixelPlaats + GREEN] = sortedConvolutieGreen[convoMid];
			rawData[pixelPlaats + BLUE] = sortedConvolutieBlue[convoMid];
		}
	}
}

int * MedianAlgorithm::sortArray(const int * convolutie) {
	int * newConvolutie = new int[convolutionSize * convolutionSize];
	unsigned int i;
	for (i = 0; i < convolutionSize * convolutionSize; i++) {
		newConvolutie[i] = convolutie[i];
	}
	quicksort(newConvolutie, 0, convolutionSize * convolutionSize -1);
	return newConvolutie;
}

int MedianAlgorithm::partition(int* input, int p, int r)
{
	int pivot = input[r];

	while (p < r)
	{
		while (input[p] < pivot)
			p++;

		while (input[r] > pivot)
			r--;

		if (input[p] == input[r])
			p++;
		else if (p < r)
		{
			int tmp = input[p];
			input[p] = input[r];
			input[r] = tmp;
		}
	}

	return r;
}

void MedianAlgorithm::quicksort(int* input, int p, int r)
{
	if (p < r)
	{
		int j = partition(input, p, r);
		quicksort(input, p, j - 1);
		quicksort(input, j + 1, r);
	}
}