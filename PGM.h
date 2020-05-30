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

	void load(std::string path) override;//Функция за прочитане на информация от изображения.
	void saveas(std::string path) const override;//Функция за запазване на информация от изображение във файл, различен от изходния.
	void print(std::ostream& out) const override;//Функция за извеждане на информация за даден формат.

	std::vector<std::vector<int>> getPixels() const;
	
	void negative() override;//Цветово обръщане.
	void rotation(std::string direction) override;//Завъртане на изображението на 90° в зависимост от зададената посока.

	void collage(std::string direction, std::string image1, std::string image2, std::string outimage) override;//Създаване на колаж.

};




#endif
