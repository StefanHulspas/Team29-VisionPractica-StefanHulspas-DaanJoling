#pragma once
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
#include "ThresholdAlgorithm.h"
#include "TransformAlgorithm.h"
#include <math.h>
#include <string>
#include <iostream> 
class GUI
{
private:
	Image img;
	bool running = true;
	void run();
	void startUp();
	void startMenu();
	void printAlgo();
	void algoList();
	void printName();
	void changeName();
	void applyAlgo();
	void wrongChoice();
	void quit();
public:
	GUI();
	~GUI();
};

