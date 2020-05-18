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

	void load(std::string path);//Функция за прочитане на информация от изображения.
	void saveas(std::string path) const;//Функция за запазване на информация от изображение във файл, различен от изходния.
	void print(std::ostream& out) const;//Функция за извеждане на информация за даден формат.

	void grayscale();//Функция, която не прави промени върху изображението, защото то е черно-бяло.
	void monochrome();//Функция, която не прави промени върху изображението, защото то е черно-бяло.
	void negative();//Цветово обръщане.
	void rotation(std::string direction);//Завъртане на изображението на 90° в зависимост от зададената посока.

	void collage(std::string direction, std::string image1, std::string image2, std::string outimage);//Създаване на колаж.

	void undoGrayscale();//Функция, която не прави промени върху изображението, защото то е черно-бяло.
	void undoMonochrome();//Функция, която не прави промени върху изображението, защото то е черно-бяло.
};




#endif
