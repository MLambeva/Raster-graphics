#include"Formats.h"


Formats::Formats (std::string path, std::string ASCIInum, std::string comment, int width, int height)
{
	this->path = path;
	this->ASCIInum = ASCIInum;
	this->comment = comment;
	this->width = width;
	this->height = height;
}

Formats::~Formats(){}

std::string Formats::getPath() const
{
	return this->path;
}

std::string Formats::getASCIInum() const
{
	return this->ASCIInum;
}

std::string Formats::getComment() const
{
	return this->comment;
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





