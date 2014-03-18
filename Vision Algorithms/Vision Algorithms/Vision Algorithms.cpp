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
#include "K_MeansClusterAlgorithm.h"
#include <iostream> 
#include <string>


int _tmain(int argc, _TCHAR* argv[])
{
	Image original("meepogroep.png");
	if (original.isCreated()) {
		/*
		Image gray(original);
		gray.applyAlgorithm(new GrayAlgorithm());
		gray.applyAlgorithm(new HistogramAlgorithm(gray.getFirstName(), 256), false);
		gray.applyAlgorithm(new HistogramAlgorithm(gray.getFirstName(), 10), false);
		gray.applyAlgorithm(new EqualizeAlgorithm());
		Image salt_pepper(original);
		salt_pepper.applyAlgorithm(new SaltAndPepperAlgorithm(50));
		Image salt_copy(salt_pepper);
		salt_pepper.applyAlgorithm(new MeanAlgorithm());
		salt_copy.applyAlgorithm(new MedianAlgorithm(5));
		Image RED(original);
		Image BLUE(original);
		Image GREEN(original);
		BLUE.applyAlgorithm(new SingleColorAlgorithm(0));
		GREEN.applyAlgorithm(new SingleColorAlgorithm(1));
		RED.applyAlgorithm(new SingleColorAlgorithm(2)); */
		Image cluster(original); 
		cluster.applyAlgorithm(new K_MeansClusterAlgorithm(20));
	}

	std::cout << "Press ENTER to continue... ";
	std::cin.ignore(std::numeric_limits <std::streamsize> ::max(), '\n');

	return 0;
}

