#pragma once
class color
{
private:
	int red;
	int green;
	int blue;
public:
	color(int red, int green, int blue);
	~color();
	int getRed() const;
	int getGreen() const;
	int getBlue() const;
	void setRed(int r);
	void setGreen(int g);
	void setBlue(int b);
};

