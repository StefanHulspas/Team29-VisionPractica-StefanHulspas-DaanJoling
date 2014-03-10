#include "stdafx.h"
#include "Image.h"
#include <iostream>

Image::~Image()
{
	delete[] name;
	delete[] type;
	FreeImage_Unload(dib);
}

Image::Image(const char * name) {
	saveNametoLowerCase(name);
	findType(this->name);
	if (compareType(".png")) {
		format = FIF_PNG;
	}
	else if (compareType(".jpg")) {
		format = FIF_JPEG;
	}

	std::cout << "Trying to access: " << this->name << '\n';
	std::cout << "Of type: " << this->type << '\n';

	dib = FreeImage_Load(format, this->name);

	width = FreeImage_GetWidth(dib);
	height = FreeImage_GetHeight(dib);
	pitch = FreeImage_GetPitch(dib);
	bpp = FreeImage_GetBPP(dib) / 8;
	if (bpp == 0) std::cout << "File not found I do believe old chap!\n";

	rawData = (BYTE*)FreeImage_GetBits(dib);
}


Image::Image(const Image& i) {
	saveNametoLowerCase(i.name);
	findType(name);

	dib = FreeImage_Clone(i.dib);
	format = i.format;

	width = FreeImage_GetWidth(dib);
	height = FreeImage_GetHeight(dib);
	pitch = FreeImage_GetPitch(dib);
	bpp = FreeImage_GetBPP(dib) / 8;
	if (bpp == 0) std::cout << "File not found I do believe old chap!\n";

	rawData = (BYTE*)FreeImage_GetBits(dib);
}

void Image::saveNametoLowerCase(const char * name) {
	unsigned int i;
	for (i = 0; name[i] != '\0'; i++);
	this->name = (char*)malloc(sizeof(char) * (i + 1));
	for (i = 0; name[i] != '\0'; i++) {
		if (name[i] >= 'A' && name[i] <= 'Z') {
			this->name[i] = name[i] - ('A' - 'a');
		}else 
			this->name[i] = name[i];
	}
	this->name[i] = '\0';
}
void Image::saveImage(char * name) {
	FreeImage_Save(format, dib, name);
}

void Image::findType(const char * name) {
	unsigned int i, j;
	for (i = 0; name[i] != '\0'; i++) if (name[i] == '.') j = i;
	type = (char*)malloc(sizeof(char)* (i - j + 1));
	for (i = 0; name[i + j] != '\0'; i++) {
		type[i] = name[i + j];
	}
	this->type[i] = '\0';
}

int Image::compareType(char * type) {
	unsigned int i;
	for (i = 0; type[i] != '\0'; i++) {
		if (this->type[i] != type[i]) return 0;
	}
	return 1;
}

int Image::getWidth() {
	return width;
}

int Image::getHeight() {
	return height;
}

int Image::getPitch() {
	return pitch;
}

int Image::getBPP() {
	return bpp;
}

BYTE * Image::getRawData() {
	return rawData;
}