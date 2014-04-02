#include "stdafx.h"
#include "Histogram.h"


double * Histogram::normalizeHistogram(unsigned char * rawData, int bpp, int height, int width, int pitch, int size) {
	//Check to see if the size is possible
	if (size != 10 && size != 256) return NULL;

	//determine the amound of pixels
	int totalPixels = width * height;
	
	//create a new array to save the values in
	int * histo = new int[size];
	int i;
	for (i = 0; i < size; i++)
		histo[i] = 0;
	
	//a value adjuster for when the size is 10
	double adjuster = 1;
	if (size == 10)
		adjuster = 10.0f / 256.0f;

	//Filling the array
	unsigned int x, y, count;
	count = 0;
	for (y = 0; y < height; y++) {
		for (x = 0; x < width * bpp; x += bpp) {
			histo[(int)((double)rawData[y * pitch + x] * adjuster)]++;
			count++;
		}
	}
	//normalize the histogram
	double * normHisto = new double[size];
	for (i = 0; i < size; i++) {
		normHisto[i] = ((float)histo[i] / (float)totalPixels);
	}
	return normHisto;
}

void Histogram::print(double * histo, int size, std::string name) {
	//creating the files name
	name += "_H" + std::to_string(size) + ".csv";
	//adding the outputfolder
	name = "Output/" + name;
	std::ofstream outputFile;
	//creating the streamreader to the file
	outputFile.open(name.c_str());
	unsigned int i;
	//writing the histogram values to the file
	for (i = 0; i < size; i++) {
		outputFile << '[' << (i + 1) << "], " << histo[i] << '\n';
	}
	outputFile.close();
}