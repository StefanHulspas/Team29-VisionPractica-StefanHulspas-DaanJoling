#include "stdafx.h"
#include "Image.h"

Image::~Image()
{
	delete[] name;
	delete[] firstName;
	delete[] type;
	FreeImage_Unload(dib);
}

Image::Image(const char * name) {
	std::string source(name);
	source = DIR_Input + source;
	if (!exists(source.c_str())) {
		std::cout << "Can't find the picture!\n";
		return;
	}
	saveNametoLowerCase(name);
	saveFirstName();
	findType(this->name);
	if (compareType(".png")) {
		format = FIF_PNG;
	}
	else if (compareType(".jpg")) {
		format = FIF_JPEG;
	}



	dib = FreeImage_Load(format, source.c_str());

	width = FreeImage_GetWidth(dib);
	height = FreeImage_GetHeight(dib);
	pitch = FreeImage_GetPitch(dib);
	bpp = FreeImage_GetBPP(dib) / 8;

	rawData = (unsigned char*)FreeImage_GetBits(dib);
	created = true;
}

Image::Image(const Image& i) {
	if (!i.created){
		std::cout << "Can't copy this image!\n";
		return;
	}
	saveNametoLowerCase(i.name);
	saveFirstName();
	findType(name);

	dib = FreeImage_Clone(i.dib);
	format = i.format;

	width = FreeImage_GetWidth(dib);
	height = FreeImage_GetHeight(dib);
	pitch = FreeImage_GetPitch(dib);
	bpp = FreeImage_GetBPP(dib) / 8;

	rawData = (unsigned char*)FreeImage_GetBits(dib);
	created = true;
}

Image::Image(int height, int width, int bpp, char * name) {
	std::string source(name);
	saveNametoLowerCase(name);
	saveFirstName();
	findType(this->name);
	if (compareType(".png")) {
		format = FIF_PNG;
	}
	else if (compareType(".jpg")) {
		format = FIF_JPEG;
	}

	dib = FreeImage_Allocate(width, height, bpp * 8, 0xFF000000, 0x00FF0000, 0x0000FF00);

	this->width = FreeImage_GetWidth(dib);
	this->height = FreeImage_GetHeight(dib);
	this->pitch = FreeImage_GetPitch(dib);
	this->bpp = FreeImage_GetBPP(dib) / 8;

	rawData = (unsigned char*)FreeImage_GetBits(dib);
	created = true;
}

void Image::saveNametoLowerCase(const char * name) {
	unsigned int i;
	for (i = 0; name[i] != '\0'; i++);
	this->name = (char*)malloc(sizeof(char)* (i + 1));
	for (i = 0; name[i] != '\0'; i++) {
		if (name[i] >= 'A' && name[i] <= 'Z') {
			this->name[i] = name[i] - ('A' - 'a');
		}else 
			this->name[i] = name[i];
	}
	this->name[i] = '\0';
}

void Image::saveFirstName() {
	unsigned int i;
	for (i = 0; name[i] != '\0' && name[i] != '.'; i++) {
		i = i;
	}
	firstName = (char*)malloc(sizeof(char)* (i + 1));
	unsigned int j;
	for (j = 0; j < i ; j++) {
		firstName[j] = name[j];
	}
	firstName[i] = '\0';
}

void Image::saveImage(const char * name) {
	std::string source(name);
	source = DIR_Output + source;
	FreeImage_Save(format, dib, source.c_str());
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

int Image::getWidth() const {
	return width;
}

int Image::getHeight() const {
	return height;
}

int Image::getPitch() const {
	return pitch;
}

int Image::getBPP() const{
	return bpp;
}

unsigned char * Image::getRawData() const {
	return rawData;
}

char * Image::getType() const{
	return type;
}

char * Image::getName() const{
	return name;
}

char * Image::getFirstName() const{
	return firstName;
}

inline bool Image::exists(const char *filename) const{
	std::ifstream ifile(filename);
	if (ifile.is_open()){
		ifile.close();
		return true;
	}
	return false;
}

bool const Image::isCreated() {
	return created;
}

void Image::print() {
	unsigned int x, y;
	for (y = 0; y < height; y++) {
		for (x = 0; x < width * bpp; x += bpp) {
			std::cout << (int)rawData[y * pitch + x] << "-" << (int)rawData[y * pitch + x + 1] << "-" << (int)rawData[y * pitch + x + 2];
			std::cout << '|' << ' ';
		}
		std::cout << '\n';
	}
}

void Image::applyAlgorithm(Algorithm* a, bool save) {
	a->doAlgorithm(*this);
	if (save) {
		std::string name = this->name;
		name = a->getName() + name;
		std::cout << "saving to: " << name.c_str() << "\n";
		saveImage(name.c_str());
	}
}