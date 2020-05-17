#ifndef FORMAT_H
#define FORMAT_H
#include<string>
#include<vector>
#include<fstream>
#include<iostream>
#include<algorithm>
#include"RGB.h"
#include"Formats.h"

class PPM:public Formats
{
private:
	int maxValue;
	std::vector<std::vector<RGB>>pixels;

public:
	PPM();
	PPM (std::string path, std::string ASCIInum, std::string comment, int width, int height, int maxValue, std::vector<std::vector<RGB>>pixels);
	~PPM();
	PPM& operator=(const PPM& other);
	int getMaxValue() const;
	RGB getPixels(int x, int y);



	void open(std::string path);
	void print(std::ostream& out) const;
	void grayscale();
	void monochrome();
	void negative();
	void rotation(std::string direction);
	void saveas(std::string path);
	void collage(std::string direction, std::string image1, std::string image2, std::string outimage);

	void undoGrayscale();
	void undoMonochrome();

};




#endif
