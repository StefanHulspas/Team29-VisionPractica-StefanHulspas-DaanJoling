#include "stdafx.h"
#include "color.h"


color::color(int red, int green, int blue) : red(red), green(green), blue(blue)
{
}


color::~color()
{
}

int color::getRed() const {
	return red;
}

int color::getGreen() const {
	return green;
}

int color::getBlue() const {
	return blue;
}

void color::setRed(int r) {
	red = r;
}

void color::setGreen(int g) {
	green = g;
}

void color::setBlue(int b) {
	blue = b;
}