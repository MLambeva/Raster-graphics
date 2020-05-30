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

	void load(std::string path) override;//Функция за прочитане на информация от изображения.
	void saveas(std::string path) const override;//Функция за запазване на информация от изображение във файл, различен от изходния.
	void print(std::ostream& out) const override;//Функция за извеждане на информация за даден формат.


	void grayscale()override;//Променя пикселите да са в сив нюанс.
	void monochrome()override;//Променя пикселите да са черни или бели.
	void negative() override;//Цветово обръщане.
	void rotation(std::string direction) override;//Завъртане на изображението на 90° в зависимост от зададената посока.
	
	void collage(std::string direction, std::string image1, std::string image2, std::string outimage) override;//Създаване на колаж.

	void undoGrayscale()override;//Функция за премахване на сиви нюанси.
	void undoMonochrome()override;//Функция за премахване на черно/бели нюанси.

};




#endif
