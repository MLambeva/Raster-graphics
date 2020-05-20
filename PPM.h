#ifndef FORMAT_H
#define FORMAT_H
#include<string>
#include<vector>
#include<fstream>
#include<iostream>
#include<algorithm>
#include<functional>
#include"RGB.h"
#include"Formats.h"

class PPM:public Formats
{
private:
	int maxValue;
	std::vector<std::vector<RGB>>pixels;

public:
	PPM();
	~PPM();

	void load(std::string path);//������� �� ��������� �� ���������� �� �����������.
	void saveas(std::string path) const;//������� �� ��������� �� ���������� �� ����������� ��� ����, �������� �� ��������.
	void print(std::ostream& out) const;//������� �� ��������� �� ���������� �� ����� ������.

	void grayscale();//������� ��������� �� �� � ��� �����.
	void monochrome();//������� ��������� �� �� ����� ��� ����.
	void negative();//������� ��������.
	void rotation(std::string direction);//��������� �� ������������� �� 90� � ���������� �� ���������� ������.
	
	void collage(std::string direction, std::string image1, std::string image2, std::string outimage);//��������� �� �����.

	void undoGrayscale();//������� �� ���������� �� ���� ������.
	void undoMonochrome();//������� �� ���������� �� �����/���� ������.

};




#endif
