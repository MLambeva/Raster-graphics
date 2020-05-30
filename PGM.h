#ifndef PGM_H
#define PGM_H
#include<iostream>
#include<fstream>
#include<vector>
#include<cassert>
#include"Formats.h"

class PGM :public Formats
{
private:
	int maxValue;
	std::vector<std::vector<int>>pixels;

public:
	PGM();
	~PGM();

	void load(std::string path) override;//������� �� ��������� �� ���������� �� �����������.
	void saveas(std::string path) const override;//������� �� ��������� �� ���������� �� ����������� ��� ����, �������� �� ��������.
	void print(std::ostream& out) const override;//������� �� ��������� �� ���������� �� ����� ������.

	std::vector<std::vector<int>> getPixels() const;
	
	void negative() override;//������� ��������.
	void rotation(std::string direction) override;//��������� �� ������������� �� 90� � ���������� �� ���������� ������.

	void collage(std::string direction, std::string image1, std::string image2, std::string outimage) override;//��������� �� �����.

};




#endif
