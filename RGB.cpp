#include"RGB.h"


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

std::ostream& operator<<(std::ostream& out, const RGB& other)
{
	//��������� �� ��������� ������ ����, ����� � �������.
	//�� ���� ����� �� ����������� �������� ��������� �� ������� ��� ����.
	if (Formats::isOneDigit(other.red)) out << "  " << other.red << " ";
	else if (Formats::isTwoDigit(other.red)) out << " " << other.red << " ";
	else if(Formats::isThreeDigit(other.red)) out << other.red << " ";
	if (Formats::isOneDigit(other.green)) out << "  " << other.green << " ";
	else if (Formats::isTwoDigit(other.green)) out << " " << other.green << " ";
	else if (Formats::isThreeDigit(other.green))out << other.green << " ";
	if (Formats::isOneDigit(other.blue)) out << "  " << other.blue << "  ";
	else if (Formats::isTwoDigit(other.blue)) out << " " << other.blue << "  ";
	else if (Formats::isThreeDigit(other.blue))out << other.blue << "  ";
	
	return out;
}
