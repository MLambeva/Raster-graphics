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
	std::vector<std::vector<bool>> pixels;

public:
	PBM();
	~PBM();

	void load(std::string path) override;//������� �� ��������� �� ���������� �� �����������.
	void saveas(std::string path) const override;//������� �� ��������� �� ���������� �� ����������� ��� ����, �������� �� ��������.
	void print(std::ostream& out) const override;//������� �� ��������� �� ���������� �� ����� ������.

	std::vector<std::vector<bool>> getPixels() const;

	void negative() override;//������� ��������.
	void rotation(std::string direction) override;//��������� �� ������������� �� 90� � ���������� �� ���������� ������.
	
	void collage(std::string direction, std::string image1, std::string image2, std::string outimage) override;//��������� �� �����.
	
};


#endif
