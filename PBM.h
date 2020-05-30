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

	void load(std::string path) override;//Функция за прочитане на информация от изображения.
	void saveas(std::string path) const override;//Функция за запазване на информация от изображение във файл, различен от изходния.
	void print(std::ostream& out) const override;//Функция за извеждане на информация за даден формат.

	std::vector<std::vector<bool>> getPixels() const;

	void negative() override;//Цветово обръщане.
	void rotation(std::string direction) override;//Завъртане на изображението на 90° в зависимост от зададената посока.
	
	void collage(std::string direction, std::string image1, std::string image2, std::string outimage) override;//Създаване на колаж.
	
};


#endif
