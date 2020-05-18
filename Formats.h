#ifndef FORMATS_H
#define FORMATS_H
#include<string>
#include<vector>


class Formats
{
protected:
	std::string path;
	std::string ASCIInum;
	std::string comment;
	int width;
	int height;

public:
	Formats() = default;
	virtual ~Formats();

	std::string getPath() const;
	

	//Често виртуални функции.
	virtual void load(std::string path) = 0;
	virtual void saveas(std::string path) const = 0;
	virtual void print(std::ostream& out) const = 0;

	virtual void grayscale() = 0;
	virtual void monochrome() = 0;
	virtual void negative() = 0;
	virtual void rotation(std::string direction) = 0;
	virtual void collage(std::string direction, std::string image1, std::string image2, std::string outimage) = 0;

	virtual void undoGrayscale() = 0;
	virtual void undoMonochrome() = 0;

	friend std::ostream& operator<<(std::ostream& out, const Formats& other);	
};


#endif
