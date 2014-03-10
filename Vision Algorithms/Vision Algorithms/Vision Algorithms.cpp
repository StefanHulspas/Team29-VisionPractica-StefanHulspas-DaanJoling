// Vision Algorithms.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Image.h"
#include "Algorithm.h"
#include "GrayAlgorithm.h"
#include <iostream>


int _tmain(int argc, _TCHAR* argv[])
{
	Image test0("Meepo.jpg");
	Image test1(test0);

	BYTE * test3 = test0.getRawData();
	
	test3[0] = 255;
	test3[test0.getPitch()] = 0;
	test0.saveImage("test0.png");
	test1.saveImage("test1.png");

	GrayAlgorithm grayScale;
	grayScale.doAlgorithm(test0);
	test0.saveImage("gray_test0.png");
	
	std::cout << "Press ENTER to continue... ";
	std::cin.ignore(std::numeric_limits <std::streamsize> ::max(), '\n');

	return 0;
}

