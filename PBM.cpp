#include"PBM.h"

PBM::PBM():Formats()
{
	this->pixels = { };
};

PBM::~PBM()
{
}

void PBM::load(std::string path)//Функция за прочитане на информация от изображения.
{
	std::ifstream input(path.c_str());//Поток за четене.

	if (input.fail())//Проверка за състоянието на потока.
	{
		std::cout << "Error!\n";
		return;
	}
	
	input >> this->ASCIInum;//Чете ASCII кода.
	assert(this->ASCIInum == "P1");//Проверка дали е коректен спрямо разширението на файла.
	
	this->path = path;//Присвоява името на файла.

	char x;
	input >> x;
	if (x == '#')//Коментарите започват с #.
	{
		input.unget();//Връща get-указателя един символ назад, т.е. преди #.
		std::getline(input, this->comment);//Прочита коментара.
	}
	else//Ако няма коментар, то значи следва да се прочете информация за ширината и височината.
	{
		input.unget();
	}

	input >> this->width;
	input >> this->height;	
	
	for (int i = 0; i < this->height; i++)
	{
		int x;
		std::vector<int> helper;//Помощна променлива, в която запазваме пикселите на всеки ред.	
		for (int j = 0; j < this->width; j++)
		{
			input >> x;//Четем всеки пиксел.
			assert(x == 0 || x == 1);
			helper.push_back(x);//Добавяме всеки пиксел.
		}
		this->pixels.push_back(helper);//Когато обходим реда, добавяме пикселите от целия ред.
	}	
	input.close();//Затваряме файла.
}

void PBM::saveas(std::string path) const//Функция за запазване на информация от изображение във файл, различен от изходния.
{
	std::ofstream saveas(path.c_str());//Поток за запис.

	saveas << this->ASCIInum << '\n';//Записваме ASCII кода.
	saveas << this->comment << '\n';//Записваме коментара.
	saveas << this->width << " " << this->height << '\n';//Записваме ширина и височина.

	for (int i = 0; i < this->height; i++)
	{
		for (int j = 0; j < this->width; j++)
		{
			assert(this->pixels[i][j] == 0 || this->pixels[i][j] == 1);
			saveas << this->pixels[i][j];//Записваме всеки пиксел.
		}
		saveas << '\n';
	}

	saveas.close();//Затваряме файла.
}

void PBM::print(std::ostream& out) const//Функция за извеждане на информация за даден формат.
{
	out << this->path << '\n';
	out << "ASCII number: " << this->ASCIInum << '\n';
	out << this->comment << '\n';
	out << "Width: " << this->width << " Height:" << this->height << '\n';
	out << "Pixels:\n";
	
	for (int i = 0; i < this->height; i++)
	{
		for (int j = 0; j < this->width; j++)
		{
			out << this->pixels[i][j] << " ";
		}
		out << '\n';
	}
}

void PBM::grayscale() {}//Функция, която не прави промени върху изображението, защото то е черно-бяло.

void PBM::monochrome() {}//Функция, която не прави промени върху изображението, защото то е черно-бяло.

void PBM::negative() //Цветово обръщане.
{
	for (int i = 0; i < this->height; i++)
	{
		for (int j = 0; j < this->width; j++)
		{
			this->pixels[i][j] = 1 - this->pixels[i][j];
		}
	}
}

void PBM::rotation(std::string direction) //Завъртане на изображението на 90° в зависимост от зададената посока.
{
	std::vector<std::vector<int>> saver;//Помощна променлива, в която запазваме пикселите на цялото изображение.

	if (direction == "left")
	{
		std::swap(this->width, this->height);//Разменяме стойностите на височината и ширината.		
				
		for (int i = this->height - 1; i >= 0; i--)
		{
			std::vector<int> helper;//Помощна променлива, в която запазваме пикселите на всеки ред.
			for (int j = 0; j < this->width; j++)
			{
				helper.push_back(this->pixels[j][i]);
			}
			saver.push_back(helper);
		}
		
	}
	else if (direction == "right")
	{
		std::swap(this->width, this->height);//Разменяме стойностите на височината и ширината.		

		for (int i = 0; i < this->height; i++)
		{
			std::vector<int> helper;//Помощна променлива, в която запазваме пикселите на всеки ред.
			for (int j = this->width - 1; j >= 0; j--)
			{
				helper.push_back(this->pixels[j][i]);
			}
			saver.push_back(helper);
		}
	}
	else
	{
		std::cout << "Wrong direction!\n";
		return;
	}
	this->pixels = saver;//Присвояваме стойностите на пикселите.
}

void PBM::collage(std::string direction, std::string image1, std::string image2, std::string outimage) 
{
	/*Създаване на колаж от две изображения (<image1>, <image2>), които са от един и същ формат и еднаква размерност в зависимост от зададена посока -
	хоризонтална или вертикална, като полученото изабражение се записва в ново изображение <outimage>*/
	std::vector<std::vector<int>> saver;//Помощна променлива, в която запазваме пикселите на цялото изображение.

	PBM firstImage;//Обект от текущия клас, в който ще съхраняваме данните за първото изображение.
	firstImage.load(image1);

	PBM secondImage;//Обект от текущия клас, в който ще съхраняваме данните за второто изображение.
	secondImage.load(image2);

	if (firstImage.height == secondImage.height && firstImage.width == secondImage.width)//Условие, което трябва да изпълняват.
	{
		if (direction == "horizontal")
		{
			this->path = outimage;
			this->ASCIInum = firstImage.ASCIInum;//ASCII номерата на 2те изображения съвпадат, защото са от един формат.
			this->comment = firstImage.comment + secondImage.comment;//Конкатенация на двата коментара.
			this->width = 2 * firstImage.width;//Ширината се увеличава два пъти.
			this->height = firstImage.height;//Височината остава същата.
			for (int i = 0; i < this->height; i++)
			{
				std::vector<int> helper;//Помощна променлива, в която запазваме пикселите на всеки ред.
				for (int j = 0; j < firstImage.width; j++)//Първо обхождаме реда на първото изображение.
				{
					helper.push_back(firstImage.pixels[i][j]);//Добавяме стойностите.
				}

				for (int t = 0; t < secondImage.width; t++)//След това обхождаме реда на второто изображение.
				{
					helper.push_back(secondImage.pixels[i][t]);//Добавяме стойностите.
				}
				saver.push_back(helper);//След преминаване по целия ред, добавяме стойностите в помощната променлива.
			}
		}
		else if (direction == "vertical")
		{
			this->path = outimage;
			this->ASCIInum = firstImage.ASCIInum;//ASCII номерата на 2те изображения съвпадат, защото са от един формат.
			this->comment = firstImage.comment + secondImage.comment;//Конкатенация на двата коментара.
			this->width = firstImage.width;//Ширината остава същата.
			this->height = 2 * firstImage.height;//Височината се увеличава два пъти.
			
			//Обхождаме всички редове на първото изображение, а след това всички редове на второто.
			size_t k = 0;//Трябва ни допълнителен брояч при обхождане на второто изображение.
			for (int i = 0; i < this->height; i++)
			{
				std::vector<int> helper;//Помощна променлива, в която запазваме пикселите на всеки ред.
				if (i < firstImage.height)
				{
					//Обхождане на първо изабражение.
					for (int j = 0; j < firstImage.width; j++)
					{
						helper.push_back(firstImage.pixels[i][j]);
					}
				}
				else if (i >= firstImage.height)
				{
					//Обхождане на второ изображение.
					for (size_t j = 0; j < this->width; j++)
					{
						helper.push_back(secondImage.pixels[k][j]);
					}
					k++;//Увеличаваме брояча, т.е. преминаваме на следващия ред.
				}
				saver.push_back(helper);//След преминаване по целия ред, добавяме стойностите в помощната променлива.
			}
		}
		else
		{
			std::cout << "Wrong direction!\n";
		}
		this->pixels = saver;//Присвояваме стойностите на пикселите.
		this->saveas(outimage);//Записваме полученото изображение.
	}
	else
	{
		std::cout << "Unable to create collage!\n";
	}
}

void PBM::undoGrayscale() {}//Функция, която не прави промени върху изображението, защото то е черно-бяло.

void PBM::undoMonochrome() {}//Функция, която не прави промени върху изображението, защото то е черно-бяло.