#ifndef PGM_H
#define PGM_H
#include<iostream>
#include<fstream>
#include<vector>
#include<cassert>
#include"Formats.h"
#include"helperFunctions.h"

class PGM :public Formats
{
private:
	int maxValue;
	std::vector<std::vector<int>>pixels;

public:
	PGM();
	~PGM();

	void load(std::string path);//������� �� ��������� �� ���������� �� �����������.
	void saveas(std::string path) const;//������� �� ��������� �� ���������� �� ����������� ��� ����, �������� �� ��������.
	void print(std::ostream& out) const;//������� �� ��������� �� ���������� �� ����� ������.

	void grayscale();//�������, ����� �� ����� ������� ����� �������������, ������ �� � �����-����.
	void monochrome();//�������, ����� �� ����� ������� ����� �������������, ������ �� � �����-����.
	void negative();//������� ��������.
	void rotation(std::string direction);//��������� �� ������������� �� 90� � ���������� �� ���������� ������.

	void collage(std::string direction, std::string image1, std::string image2, std::string outimage);//��������� �� �����.

	void undoGrayscale();//�������, ����� �� ����� ������� ����� �������������, ������ �� � �����-����.
	void undoMonochrome();//�������, ����� �� ����� ������� ����� �������������, ������ �� � �����-����.
};




#endif
