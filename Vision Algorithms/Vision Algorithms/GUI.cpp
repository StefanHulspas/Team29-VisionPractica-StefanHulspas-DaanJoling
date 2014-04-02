#include "stdafx.h"
#include "GUI.h"

#define PI 3.14159265

GUI::GUI() : img("face.png")
{
	run();
}


GUI::~GUI()
{
}

void GUI::run() {
	startUp();
	std::cout << "Currently using default picture: " << img.getName() << '\n';
	while (running) {
		startMenu();
		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
		}
	}
}

void GUI::startUp() {
	std::cout << "Welcome in a picture transform program\n";
	std::cout << "Made by Stefan Hulspas\n\n";
}
void GUI::startMenu() {
	std::cout << "What would you like to do?\n";
	std::cout << "1. Print all possible algorithms\n";
	std::cout << "2. Print the current picture's name\n";
	std::cout << "3. Select a new picture\n";
	std::cout << "4. Apply an algorithm to the picture\n";
	std::cout << "5. Quit\n\n";
	int choice;
	std::cin >> choice;
	switch (choice) {
	case 1: printAlgo();
		return;
	case 2: printName();
		return;
	case 3: changeName();
		return;
	case 4:applyAlgo();
		return;
	case 5: quit();
		return;
	default: wrongChoice();
	}
}

void GUI::printAlgo() {
	std::cout << "Currently I know 10 algorithms:\n";
	algoList();
	std::cout << '\n';
}
void GUI::algoList() {
	std::cout << "1. Grayscaling\n";
	std::cout << "2. Creating a histogram\n";
	std::cout << "3. Equalizing\n";
	std::cout << "4. Adding salt and pepper Noise\n";
	std::cout << "5. Applying a mean filter\n";
	std::cout << "6. Applying a median filter\n";
	std::cout << "7. Showing a single color\n";
	std::cout << "8. Applying a K means cluster filter\n";
	std::cout << "9. Determining the threshold\n";
	std::cout << "10.Transforming the image\n";
}

void GUI::printName() {
	if (img.isCreated())
		std::cout << "The picture currently in the program is: " << img.getName() << '\n' << '\n';
	else {
		std::cout << "Something went wrong finding the picture, lets start over.\n\n";
	}
}

void GUI::changeName() {
	std::cout << "Please enter the name of the picture you would like the change.\n";
	std::cout << "Make sure its in the input folder and add the extention.\n";
	std::string name;
	std::getline(std::cin, name);
	std::getline(std::cin, name);
	img = *new Image(name.c_str());
	printName();
}

void GUI::applyAlgo(){
	bool more = false;
	if (!img.isCreated()) {
		std::cout << "I'm sorry I can't apply anything to something that isn't there.\n\n";
		return;
	}
	int choice;
	do {
		std::cout << "Which Algorithm would you like to run?\n";
		algoList();
		std::cin >> choice;
		switch (choice) {
		case 1: {
					img.applyAlgorithm(new GrayAlgorithm());
					break;
		}
		case 2: {
					std::cout << "Which size would you like to use for the histogram? 10/256\n";
					int size;
					std::cin >> size;
					if (size == 10 || size == 256) {
						img.applyAlgorithm(new HistogramAlgorithm(img.getName(), size), false);
					}
					else {
						wrongChoice();
					}
					break;
		}
		case 3:{
				   img.applyAlgorithm(new EqualizeAlgorithm());
				   break;
		}
		case 4: {
					std::cout << "How much noise would you like? 0-100\n";
					int noise;
					std::cin >> noise;
					if (noise >= 0 && noise <= 100) {
						img.applyAlgorithm(new SaltAndPepperAlgorithm(noise));
					}
					else {
						wrongChoice();
					}
					break;
		}
		case 5: {
					std::cout << "Which convolution size would you like to use? odd number > 3\n";
					int convo;
					std::cin >> convo;
					if (convo >= 3 && convo % 2 == 1) {
						img.applyAlgorithm(new MeanAlgorithm(convo));
					}
					else {
						wrongChoice();
					}
					break;
		}
		case 6: {
					std::cout << "Which convolution size would you like to use? odd number > 3\n";
					int convo;
					std::cin >> convo;
					if (convo >= 3 && convo % 2 == 1) {
						img.applyAlgorithm(new MedianAlgorithm(convo));
					}
					else {
						wrongChoice();
					}
					break;
		}
		case 7: {
					std::cout << "Which color would you like to see?\n";
					std::cout << "	1. Blue\n";
					std::cout << "	2. Green\n";
					std::cout << "	3. Red\n";
					int color;
					std::cin >> color;
					if (color > 0 && color < 4) {
						img.applyAlgorithm(new SingleColorAlgorithm(color));
					}
					else {
						wrongChoice();
					}
					break;
		}
		case 8: {
					std::cout << "How many clusters would you like? 1 - 99\n";
					int clusters;
					std::cin >> clusters;
					if (clusters > 0 && clusters < 100) {
						img.applyAlgorithm(new K_MeansClusterAlgorithm(clusters));
					}
					else {
						wrongChoice();
					}
					break;
		}
		case 9: {
					img.applyAlgorithm(new ThresholdAlgorithm());
					break;
		}
		case 10: {

					 char input = 'n';
					 std::cout << "Which scaling factor would you like to use? 1 or higher\n";
					 double factor;
					 std::cin >> factor;
					 if (factor <= 0) {
						 wrongChoice();
						 break;
					 }
					 factor = 1 / factor;
					 std::cout << "With how many degrees would you like to turn?\n";
					 int degrees;
					 std::cin >> degrees;
					 std::cout << "Which order would you like to use? 0/1\n";
					 int orde;
					 std::cin >> orde;
					 if (orde < 0 || orde > 1) {
						 wrongChoice();
						 break;
					 }
					 if (orde == 1 && factor == 1) {
						 std::cout << "Would you like to save the resized pictured? y/n\n";
						 std::cin >> input;
						 if (input != 'y' && input != 'n') {
							 wrongChoice();
							 break;
						 }
					 }
					 else {
						 std::cout << "I can only resize the picture in firstorder and without scaling.\n";
					 }
					 double matrix[9] = {
						 factor * cos(degrees*PI / 180), factor * sin(degrees*PI / 180), 0,
						 factor * -sin(degrees*PI / 180), factor * cos(degrees*PI / 180), 0,
						 0, 0, 1 };
					 img.applyAlgorithm(new TransformAlgorithm(matrix, orde, input == 'y'));
					 break;
		}
		default:
			wrongChoice();
		}
		std::cout << "would you like to run an other Algorithm?";
		char input;
		std::cin >> input;
		if (input != 'y' && input != 'n') {
			wrongChoice();
		}
		else {
			more = input == 'y';
		}
	} while (more);
}

void GUI::quit() {
	running = false;
	std::cout << "I'm sorry to see you go. Bye bye.\n";
}

void GUI::wrongChoice() {
	std::cout << "I'm sorry you can't follow instructions!\n";
	std::cout << "Lets start again shall we. \n\n";
}