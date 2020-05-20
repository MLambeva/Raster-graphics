#include"Formats.h"


Formats::~Formats()
{
}

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






