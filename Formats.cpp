#include"Formats.h"


Formats::Formats(std::string ASCIInum, std::string path, int width, int height)
{
	this->ASCIInum = ASCIInum;
	this->path = path;
	this->width = width;
	this->height = height;
}

Formats::~Formats(){}

std::string Formats::getASCIInum() const
{
	return this->ASCIInum;
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

void Formats::setWidth(int width)
{
	this->width = width;
}

void Formats::setHeight(int height)
{
	this->height = height;
}





