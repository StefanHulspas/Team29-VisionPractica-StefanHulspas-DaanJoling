#include "stdafx.h"
#include "TransformAlgorithm.h"
#include "Image.h"
#include <math.h>


TransformAlgorithm::TransformAlgorithm(double * matrix, unsigned int orde, bool resize) : Algorithm("FirstOrder_"), matrix(matrix), resize(resize)
{
	if (orde > 1) orde = 1;
	this->orde = orde;
	char * newName = (char*)malloc(sizeof(char*)* 11);

	if (orde == 0) {
		newName[0] = 'Z';
		newName[1] = 'e';
		newName[2] = 'r';
		newName[3] = 'o';
		newName[4] = '_';

		int i;
		for (i = 0; i < 6; i++) {
			newName[i + 5] = name[i+ 5];
		}
		newName[i + 5] = '\0';
		name = newName;
	}
}


TransformAlgorithm::~TransformAlgorithm()
{
	delete[] matrix;
}


void TransformAlgorithm::doAlgorithm(Image& img) {
	if (orde == 0) zeroOrder(img);
	else if (orde == 1) firstOrder(img);
}
	
void TransformAlgorithm::zeroOrder(Image& img) {
	unsigned char * rawData = img.getRawData();
	int bpp = img.getBPP();
	int height = img.getHeight();
	int width = img.getWidth();
	int pitch = img.getPitch();
	int * outputData = new int[height * pitch];
	unsigned int x, y;
	double oldX, oldY;

	for (y = 0; y < height; y++) {
		for (x = 0; x < width; x++) {
			oldX = (int)(x - matrix[2]) * matrix[0] + (int)(y - matrix[5]) * matrix[1];
			oldY = (int)(x - matrix[2]) * matrix[3] + (int)(y - matrix[5]) * matrix[4];
			oldX = round(oldX) * bpp;
			oldY = round(oldY);
			if (oldX >= 0 && oldX < width * bpp && oldY >= 0 && oldY < height) {
				outputData[y * pitch + x*bpp + RED] = rawData[(int)oldY * pitch + (int)oldX + RED];
				outputData[y * pitch + x*bpp + GREEN] = rawData[(int)oldY * pitch + (int)oldX + GREEN];
				outputData[y * pitch + x*bpp + BLUE] = rawData[(int)oldY * pitch + (int)oldX + BLUE];
			}
			else {
				outputData[y * pitch + x*bpp + RED] = 0;
				outputData[y * pitch + x*bpp + GREEN] = 0;
				outputData[y * pitch + x*bpp + BLUE] = 0;
			}
		}
	}
	for (y = 0; y < height; y++) {
		for (x = 0; x < pitch; x += bpp) {
			rawData[y * pitch + x + RED] = outputData[y * pitch + x + RED];
			rawData[y * pitch + x + GREEN] = outputData[y * pitch + x + GREEN];
			rawData[y * pitch + x + BLUE] = outputData[y * pitch + x + BLUE];
		}
	}
}

void TransformAlgorithm::firstOrder(Image& img) {
	unsigned char * rawData = img.getRawData();
	int bpp = img.getBPP();
	int height = img.getHeight();
	int width = img.getWidth();
	int pitch = img.getPitch();
	unsigned char* outputData = new unsigned char[height * pitch];
	unsigned int x, y, z, pixel;
	double oldX, oldY;
	double * distance = new double[2];
	double outputRed, outputGreen, outputBlue;
	for (y = 0; y < height; y++) {
		for (x = 0; x < width; x++) {
			oldX = (int)(x - matrix[2]) * matrix[0] + (int)(y - matrix[5]) * matrix[1];
			oldY = (int)(x - matrix[2]) * matrix[3] + (int)(y - matrix[5]) * matrix[4];
			determineDistanceValue(distance, oldX, oldY);
			oldX = floor(oldX) * bpp;
			oldY = floor(oldY);
			//check if the new value is in the picture, otherwise make it black.
			if (oldX >= 0 && oldX < width * bpp && oldY >= 0 && oldY < height) {
				pixel = (int)oldY * pitch + (int)oldX;
				outputBlue = ((1 - distance[0]) * rawData[pixel + BLUE] + distance[0] * rawData[pixel + bpp + BLUE]) * (1 - distance[1]);
				outputGreen = ((1 - distance[0]) * rawData[pixel + GREEN] + distance[0] * rawData[pixel + bpp + GREEN]) * (1 - distance[1]);
				outputRed = ((1 - distance[0]) * rawData[pixel + RED] + distance[0] * rawData[pixel + bpp + RED]) * (1 - distance[1]);
				outputBlue += ((1 - distance[0]) * rawData[pixel + pitch + BLUE] + distance[0] * rawData[pixel + pitch + bpp + BLUE]) * distance[1];
				outputGreen += ((1 - distance[0]) * rawData[pixel + pitch + GREEN] + distance[0] * rawData[pixel + pitch + bpp + GREEN]) * distance[1];
				outputRed += ((1 - distance[0]) * rawData[pixel + pitch + RED] + distance[0] * rawData[pixel + pitch + bpp + RED]) * distance[1];
				outputData[y * pitch + x * bpp + RED] = outputRed;
				outputData[y * pitch + x * bpp + GREEN] = outputGreen;
				outputData[y * pitch + x * bpp + BLUE] = outputBlue;
			}
			else {
				outputData[y * pitch + x*bpp + RED] = 0;
				outputData[y * pitch + x*bpp + GREEN] = 0;
				outputData[y * pitch + x*bpp + BLUE] = 0;
			}
		}
	}
	if (resize) firstOrderResize(img);
	for (y = 0; y < height; y++) {
		for (x = 0; x < pitch; x += bpp) {
			rawData[y * pitch + x + RED] = outputData[y * pitch + x + RED];
			rawData[y * pitch + x + GREEN] = outputData[y * pitch + x + GREEN];
			rawData[y * pitch + x + BLUE] = outputData[y * pitch + x + BLUE];
		}
	}
}

void TransformAlgorithm::firstOrderResize(Image& img) {
	unsigned char * rawData = img.getRawData();
	int bpp = img.getBPP();
	int height = img.getHeight();
	int width = img.getWidth();
	int pitch = img.getPitch();
	int newHeight, newWidth;
	newHeight = abs(matrix[1] * (double)width) + abs(matrix[0] * (double)height);
	newWidth = abs(matrix[0] * (double)width) + abs(matrix[1] * (double)height);
	if (matrix[0] >= 0 && matrix[1] >= 0) {
		matrix[2] = -matrix[1] * height;
	}
	else if (matrix[1] >= 0 && matrix[0] < 0) {
		matrix[2] = -newWidth;
		matrix[5] = matrix[0] * width;
	}
	else if (matrix[0] < 0 && matrix[1] < 0) {
		matrix[2] = matrix[0] * width;
		matrix[5] = -newHeight;
	}
	else {
		matrix[5] = matrix[1] * height;
	}

	Image newImg(newHeight, newWidth, bpp, img.getName());
	matrix[5] = matrix[5];
	matrix[2] = matrix[2];
	int pitchNew = newImg.getPitch();
	unsigned char * newRawData = newImg.getRawData();
	unsigned int x, y, z, pixel;
	double oldX, oldY;
	double * distance = new double[2];
	double outputRed, outputGreen, outputBlue;
	for (y = 0; y < newHeight; y++) {
		for (x = 0; x < newWidth; x++) {
			oldX = (int)(x + matrix[2]) * matrix[0] + (int)(y + matrix[5]) * matrix[1];
			oldY = (int)(x + matrix[2]) * matrix[3] + (int)(y + matrix[5]) * matrix[4];
			determineDistanceValue(distance, oldX, oldY);
			oldX = floor(oldX) * bpp;
			oldY = floor(oldY);
			//check if the new value is in the picture, otherwise make it black.
			if (oldX >= 0 && oldX < width * bpp && oldY >= 0 && oldY < height) {
				pixel = (int)oldY * pitch + (int)oldX;
				outputBlue = ((1 - distance[0]) * rawData[pixel + BLUE] + distance[0] * rawData[pixel + bpp + BLUE]) * (1 - distance[1]);
				outputGreen = ((1 - distance[0]) * rawData[pixel + GREEN] + distance[0] * rawData[pixel + bpp + GREEN]) * (1 - distance[1]);
				outputRed = ((1 - distance[0]) * rawData[pixel + RED] + distance[0] * rawData[pixel + bpp + RED]) * (1 - distance[1]);
				outputBlue += ((1 - distance[0]) * rawData[pixel + pitch + BLUE] + distance[0] * rawData[pixel + pitch + bpp + BLUE]) * distance[1];
				outputGreen += ((1 - distance[0]) * rawData[pixel + pitch + GREEN] + distance[0] * rawData[pixel + pitch + bpp + GREEN]) * distance[1];
				outputRed += ((1 - distance[0]) * rawData[pixel + pitch + RED] + distance[0] * rawData[pixel + pitch + bpp + RED]) * distance[1];
				newRawData[y * pitchNew + x * bpp + RED] = outputRed;
				newRawData[y * pitchNew + x * bpp + GREEN] = outputGreen;
				newRawData[y * pitchNew + x * bpp + BLUE] = outputBlue;
			}
			else {
				newRawData[y * pitchNew + x*bpp + RED] = 0;
				newRawData[y * pitchNew + x*bpp + GREEN] = 0;
				newRawData[y * pitchNew + x*bpp + BLUE] = 0;
			}
		}
	}
	std::string name = newImg.getName();
	name = this->name + name;
	name = "resized_" + name;
	std::cout << "saving to resize: " << name.c_str() << "\n";
	newImg.saveImage(name.c_str());
}

int TransformAlgorithm::round(double number) {
	return floor(number + 0.5);
}

void TransformAlgorithm::determineDistanceValue(double * distance, double x, double y) {
	double newX = x - floor(x);
	double newY = y - floor(y);
	if (newX < 0) newX *= -1;
	if (newY < 0) newY *= -1;
	if (orde == 1) {
		distance[0] = newX;
		distance[1] = newY;
 	}
}