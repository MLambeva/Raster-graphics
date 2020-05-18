#include"Formats.h"


Formats::~Formats()
{
}

std::string Formats::getPath() const
{
	return this->path;
}

std::ostream& operator<<(std::ostream& out, const Formats& other)
{
	other.print(out);
	return out;
}




