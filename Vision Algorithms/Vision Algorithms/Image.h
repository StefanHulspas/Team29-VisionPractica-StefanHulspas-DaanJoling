#pragma once

#include "FreeImage.h" 
#include <iostream>
#include <fstream>
#include "Algorithm.h"

class Image
{
private:
	char * DIR_Input = "Input/";
	char * DIR_Output = "Output/";
	FREE_IMAGE_FORMAT format;
	unsigned int width;
	unsigned int height;
	unsigned int pitch;
	unsigned int bpp;
	unsigned char * rawData;
	FIBITMAP * dib;
	char * name;
	char * firstName;
	char * type;
	bool created = false;

	Image(){}
	void saveNametoLowerCase(const char * name);
	void saveFirstName();
	int compareType(char * type);
	void findType(const char * name);
	inline bool exists(const char * name);

public:
	~Image();
	Image(const char * name);
	Image(const Image& i);
	Image(const Image* i);
	int getWidth();
	int getHeight();
	int getPitch();
	int getBPP();
	char * getType();
	char * getName();
	char * getFirstName();
	unsigned char * getRawData();
	void saveImage(const char * name);
	const bool isCreated();
	void applyAlgorithm(Algorithm* a, bool save = true);
	void print();
};

