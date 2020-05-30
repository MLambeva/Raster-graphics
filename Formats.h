#ifndef FORMATS_H
#define FORMATS_H
#include<string>
#include<vector>
#include<iostream>


class Formats
{
protected:
	std::string path;
	std::string ASCIInum;
	std::string comment;
	int width = 0;
	int height = 0;

public:
	Formats() = default;
	virtual ~Formats();

	std::string getPath() const;
	int getWidth() const;
	int getHeight() const;
	

	//Често виртуални функции.
	virtual void load(std::string path) = 0;
	virtual void saveas(std::string path) const = 0;
	virtual void print(std::ostream& out) const = 0;

	virtual void grayscale();	
	virtual void monochrome();

	virtual void negative() = 0;
	virtual void rotation(std::string direction) = 0;
	virtual void collage(std::string direction, std::string image1, std::string image2, std::string outimage) = 0;

	virtual void undoGrayscale();
	virtual void undoMonochrome();

	friend std::ostream& operator<<(std::ostream& out, const Formats& other);	

	static bool isOneDigit(int x);
	static bool isTwoDigit(int x);
	static bool isThreeDigit(int x);	
};


#endif
