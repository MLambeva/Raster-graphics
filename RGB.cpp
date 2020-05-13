#include"RGB.h"
#include<cassert>


int RGB::getRed() const
{
	return this->red;
}

int RGB::getGreen() const
{
	return this->green;
}

int RGB::getBlue() const
{
	return this->blue;
}

void RGB::setRed(const int &red)
{
	assert(red >= 0 && red <= 255);
	this->red = red;
}

void RGB::setGreen(const int &green)
{
	assert(green >= 0 && green <= 255);
	this->green = green;
}

void RGB::setBlue(const int &blue)
{
	assert(blue >= 0 && blue <= 255);
	this->blue = blue;
}

RGB RGB::setColor(int red, int green, int blue)
{
	(*this).setRed(red);
	(*this).setGreen(green);
	(*this).setBlue(blue);
	return *this;
}

bool isOneDigit(int x)
{
	return x >= 0 && x <= 9;
}

bool isTwoDigit(int x)
{
	return x >= 10 && x <= 99;
}

bool isThreeDigit(int x)
{
	return x >= 100 && x <= 255;
}

std::ostream& operator<<(std::ostream& out, const RGB& other)
{
	//out << '{' << other.red << ',' << other.green << ',' << other.blue << "}";
	if (isOneDigit(other.red)) out << "  " << other.red << " ";
	else if (isTwoDigit(other.red)) out << " " << other.red << " ";
	else if(isThreeDigit(other.red)) out << other.red << " ";
	if (isOneDigit(other.green)) out << "  " << other.green << " ";
	else if (isTwoDigit(other.green)) out << " " << other.green << " ";
	else if (isThreeDigit(other.green))out << other.green << " ";
	if (isOneDigit(other.blue)) out << "  " << other.blue << "  ";
	else if (isTwoDigit(other.blue)) out << " " << other.blue << "  ";
	else if (isThreeDigit(other.blue))out << other.blue << "  ";
	//out << other.red << " " << other.green << " " << other.blue << " ";
	return out;
}
//std::ostream& operator<<(std::ostream& out, const RGB& other)
//{
//	//out << '{' << other.red << ',' << other.green << ',' << other.blue << "}";
//	out << other.red << " " << other.green << " " << other.blue ;
//		return out;
//}