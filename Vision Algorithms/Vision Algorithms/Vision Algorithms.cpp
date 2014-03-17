// Vision Algorithms.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Image.h"
#include "Algorithm.h"
#include "GrayAlgorithm.h"
#include "HistogramAlgorithm.h"
#include "EqualizeAlgorithm.h"
#include "SaltAndPepperAlgorithm.h"
#include "MeanAlgorithm.h"
#include "MedianAlgorithm.h"
#include "SingleColorAlgorithm.h"
#include <iostream> 
#include <string>


int _tmain(int argc, _TCHAR* argv[])
{
	Image original("meepo.jpg");
	if (original.isCreated()) {
		Image gray(original);
		gray.applyAlgorithm(new GrayAlgorithm());
		gray.applyAlgorithm(new HistogramAlgorithm(gray.getFirstName(), 256), false);
		gray.applyAlgorithm(new HistogramAlgorithm(gray.getFirstName(), 10), false);
		gray.applyAlgorithm(new EqualizeAlgorithm());
		Image salt_pepper(original);
		salt_pepper.applyAlgorithm(new SaltAndPepperAlgorithm(50));
		Image salt_copy(salt_pepper);
		salt_pepper.applyAlgorithm(new MeanAlgorithm());
		salt_copy.applyAlgorithm(new MedianAlgorithm(7));
		Image RED(salt_copy);
		Image BLUE(salt_copy);
		Image GREEN(salt_copy);
		BLUE.applyAlgorithm(new SingleColorAlgorithm(0));
		GREEN.applyAlgorithm(new SingleColorAlgorithm(1));
		RED.applyAlgorithm(new SingleColorAlgorithm(2));
	}

	std::cout << "Press ENTER to continue... ";
	std::cin.ignore(std::numeric_limits <std::streamsize> ::max(), '\n');

	return 0;
}

