#include"Formats.h"


Formats::Formats(std::string ASCIInum, int width, int height)
{
	this->ASCIInum = ASCIInum;
	this->width = width;
	this->height = height;
}

Formats::~Formats(){}

std::string Formats::getASCIInum() const
{
	return this->ASCIInum;
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

