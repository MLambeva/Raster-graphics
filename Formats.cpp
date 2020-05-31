#include"Formats.h"


Formats::~Formats(){}

std::string Formats::getPath() const
{
	return this->path;
}

int Formats::getWidth() const
{
	return this->width;
}

int Formats::getHeight() const
{
	return this->height;
}

std::ostream& operator<<(std::ostream& out, const Formats& other)
{
	other.print(out);
	return out;
}

void Formats::grayscale()
{
	std::cout << "Cannot edit image with path: " << this->path<<'\n';
}

void Formats::monochrome()
{
	std::cout << "Cannot edit image with path: " << this->path << '\n';
}

void Formats::undoGrayscale()
{
	std::cout << "Cannot edit image with path: " << this->path << '\n';
}

void Formats::undoMonochrome()
{
	std::cout << "Cannot edit image with path: " << this->path << '\n';
}

bool Formats::isOneDigit(int x)
{
	return x >= 0 && x <= 9;
}

bool Formats::isTwoDigit(int x)
{
	return x >= 10 && x <= 99;
}

bool Formats::isThreeDigit(int x)
{
	return x >= 100 && x <= 255;
}



