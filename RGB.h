#ifndef RGB_H
#define RGB_H
#include<string>
#include<iostream>
#include<cassert>
#include "helperFunctions.h"

//Чрез този клас лесно ще четем .ppm изображение от файл, защото той обособява един пиксел.
class RGB 
{
private:
	int red;
	int green;
	int blue;
public:
	RGB() :red(0), green(0), blue(0) {};

	int getRed() const;
	int getGreen() const;
	int getBlue() const;

	void setRed(const int &red);
	void setGreen(const int &green);
	void setBlue(const int &blue);

	RGB setColor(int red, int green, int blue);

	friend std::ostream& operator << (std::ostream& out, const RGB& other);
};


#endif