#pragma once

#include "FreeImage.h" 
#include <iostream>
#include <fstream>
#include "Algorithm.h"

class Algorithm;

class Image
{
private:
	//Folder name from where pictures are loaded
	char * DIR_Input = "Input/";
	//Folder name where pictures are saved
	char * DIR_Output = "Output/";

	//Information about the picture so the library is only used for loading and saving
	FREE_IMAGE_FORMAT format;
	unsigned int width;
	unsigned int height;
	unsigned int pitch;
	unsigned int bpp;
	unsigned char * rawData;
	FIBITMAP * dib;

	//Full name
	char * name;
	//Picture name without its extention
	char * firstName;
	//The extention
	char * type;
	//A variable to see if its actually created
	bool created = false;


	Image(){}
	//Method to changed the name to lowercase and save it
	void saveNametoLowerCase(const char * name);
	//Method to save the name without extention
	void saveFirstName();
	//Method to compare the extention with something of your choice
	int compareType(char * type);
	//Find the extention in the name
	void findType(const char * name);
	//Method to check if the file exists
	inline bool exists(const char * name) const;

public:
	~Image();
	//Constructor to create an Image with a name
	Image(const char * name);
	//Copy Constructor
	Image(const Image& i);
	//Constructor to create a brand new picture
	Image(int height, int width, int bpp, char * name);

	//Getters
	int getWidth() const;
	int getHeight() const;
	int getPitch() const;
	int getBPP() const;
	char * getType() const;
	char * getName() const;
	char * getFirstName() const;
	unsigned char * getRawData() const;
	const bool isCreated();
	//Methode to save the image under a certain name
	void saveImage(const char * name);
	//Method to apply an algorithm to the picture
	void applyAlgorithm(Algorithm* a, bool save = true);
	//Test Method to print the pictures data
	//Don't run this with big pictures
	void print();
};

