#include "stdafx.h"
#include "Histogram.h"


double * Histogram::normalizeHistogram(unsigned char * rawData, int bpp, int height, int width, int pitch, int size) {
	if (size != 10 && size != 256) return NULL;
	int totalPixels = width * height;
	
	int * histo = new int[size];
	int i;
	for (i = 0; i < size; i++)
		histo[i] = 0;
	
	double adjuster = 1;
	if (size == 10)
		adjuster = 10.0f / 256.0f;

	unsigned int x, y, count;
	count = 0;
	for (y = 0; y < height; y++) {
		for (x = 0; x < width * bpp; x += bpp) {
			histo[(int)((double)rawData[y * pitch + x] * adjuster)]++;
			count++;
		}
	}
	count = count;
	totalPixels = totalPixels;
	double * normHisto = new double[size];
	double * totalNormHisto = new double[size];
	for (i = 0; i < size; i++) {
		normHisto[i] = ((float)histo[i] / (float)totalPixels);
	}
	return normHisto;
}

void Histogram::print(double * histo, int size, std::string name) {
	name += "_H" + std::to_string(size) + ".csv";
	name = "Output/" + name;
	std::ofstream outputFile;
	outputFile.open(name.c_str());
	unsigned int i;
	for (i = 0; i < size; i++) {
		outputFile << '[' << (i + 1) << "], " << histo[i] << '\n';
	}
	outputFile.close();
}