#pragma once

#include "FreeImage.h" 
//#include "Algorithm.h"

class Image
{
private:
	FREE_IMAGE_FORMAT format;
	unsigned int width;
	unsigned int height;
	unsigned int pitch;
	unsigned int bpp;
	BYTE * rawData;
	FIBITMAP * dib;

	Image(){}
	void saveNametoLowerCase(const char * name);
	int compareType(char * type);
	void findType(const char * name);
	char * name;
	char * type;
public:
	~Image();
	Image(const char * name);
	Image(const Image& i);
	int getWidth();
	int getHeight();
	int getPitch();
	int getBPP();
	BYTE * getRawData();
	void saveImage(char * name);
};

