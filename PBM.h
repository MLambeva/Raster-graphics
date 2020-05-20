#ifndef PBM_H
#define PBM_H
#include<vector>
#include<string>
#include<fstream>
#include<iostream>
#include<cassert>
#include"Formats.h"

class PBM:public Formats
{
private:
	std::vector<std::vector<int>> pixels;

public:
	PBM();
	~PBM();

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