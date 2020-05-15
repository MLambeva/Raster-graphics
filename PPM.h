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
	PPM(std::string ASCIInum, std::string path, int width, int height, int maxValue, std::vector<std::vector<RGB>>pixels);
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
	void save(std::string path);

	void undoGrayscale();
	void undoMonochrome();

};




#endif
