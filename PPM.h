#ifndef FORMAT_H
#define FORMAT_H
#include<string>
#include<vector>
#include<fstream>
#include<iostream>
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

	void load(std::string path) override;//������� �� ��������� �� ���������� �� �����������.
	void saveas(std::string path) const override;//������� �� ��������� �� ���������� �� ����������� ��� ����, �������� �� ��������.
	void print(std::ostream& out) const override;//������� �� ��������� �� ���������� �� ����� ������.


	void grayscale()override;//������� ��������� �� �� � ��� �����.
	void monochrome()override;//������� ��������� �� �� ����� ��� ����.
	void negative() override;//������� ��������.
	void rotation(std::string direction) override;//��������� �� ������������� �� 90� � ���������� �� ���������� ������.
	
	void collage(std::string direction, std::string image1, std::string image2, std::string outimage) override;//��������� �� �����.

	void undoGrayscale()override;//������� �� ���������� �� ���� ������.
	void undoMonochrome()override;//������� �� ���������� �� �����/���� ������.

};




#endif
