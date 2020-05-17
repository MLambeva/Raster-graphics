#include"PPM.h"
#include<cassert>


PPM::PPM() : Formats(), maxValue(0), pixels({ }) {};

PPM::PPM(std::string path, std::string ASCIInum, std::string comment, int width, int height, int maxValue, std::vector<std::vector<RGB>>pixels)
	:Formats(path, ASCIInum, comment, width, height)
{
	this->maxValue = maxValue;
	this->pixels = pixels;
}

PPM::~PPM()
{
}

PPM& PPM::operator=(const PPM& other)
{
	if (this != &other)
	{
		this->path = other.path;
		this->ASCIInum = other.ASCIInum;
		this->comment = other.comment;
		this->width = other.width;
		this->height = other.height;
		this->maxValue = maxValue;
		this->pixels = other.pixels;
	}
	return (*this);
}

int PPM::getMaxValue() const
{
	return this->maxValue;
}

RGB PPM::getPixels(int x, int y)
{
	return pixels[x][y];
}

void PPM::open(std::string path)
{
	std::ifstream input(path.c_str());

	if (input.fail())
	{
		std::cout << "Error!\n";
		return;
	}

	//std::string ASCIInum;
	input >> this->ASCIInum;
	//if (ASCIInum != "P3")//Няма смисъл, когато направя и за другите формати. 
	//{
	//	input.close();
	//	return;
	//}
	
	this->path = path;
	
	char x;
	input >> x;
	
	if (x == '#')
	{
		input.unget();
		std::getline(input, this->comment);
	}
	else
	{
		input.unget();
	}
	
	input >> this->width;	
	input >> this->height;	
	input >> this->maxValue;

	int red, green, blue;
	for (int i = 0; i < this->height; i++)
	{
		std::vector<RGB> helper;
		for (int j = 0; j < this->width; j++)
		{
			RGB saver;
			input.ignore();
			input >> red >> green >> blue;
	
			saver.setColor(red, green, blue);
		
			helper.push_back(saver);
			
		}
		this->pixels.push_back(helper);
	}	
	input.close();
}

void PPM::print(std::ostream& out) const
{
	out << this->path << '\n';
	out << "ASCII number: " << this->ASCIInum << '\n';
	out << this->comment << '\n';
	out << "Width: " << this->width << " Height:" << this->height <<'\n';
	out << "Max value: " << this->maxValue <<'\n';
	out << "Pixels:\n";
	for (int i = 0; i < this->height; i++)
	{
		for (int j = 0; j < this->width; j++)
		{
			out << this->pixels[i][j];
		}
		out << '\n';
	}
}

void PPM::grayscale()
{
	for (int i = 0; i < this->height; i++)
	{
		for (int j = 0; j < this->width; j++)
		{
			if ((this->pixels[i][j].getRed() != this->pixels[i][j].getGreen() || this->pixels[i][j].getRed() != this->pixels[i][j].getBlue()))
			{
				//Формула от tutorialspoint.com
				this->pixels[i][j].setRed(0.3 * this->pixels[i][j].getRed());
				this->pixels[i][j].setGreen(0.59 * this->pixels[i][j].getGreen());
				this->pixels[i][j].setBlue(0.11 * this->pixels[i][j].getBlue());
			}
		}
	}
}

void PPM::monochrome()
{
	for (int i = 0; i < this->height; i++)
	{
		for (int j = 0; j < this->width; j++)
		{
			if (this->pixels[i][j].getRed() != this->pixels[i][j].getGreen() || this->pixels[i][j].getRed() != this->pixels[i][j].getBlue())
			{
				this->pixels[i][j].setRed(255);
				this->pixels[i][j].setGreen(255);
				this->pixels[i][j].setBlue(255);
			}
		}
	}
}

void PPM::negative()
{
	for (int i = 0; i < this->height; i++)
	{
		for (int j = 0; j < this->width; j++)
		{
			this->pixels[i][j].setRed(this->maxValue - this->pixels[i][j].getRed());//255
			this->pixels[i][j].setGreen(this->maxValue - this->pixels[i][j].getGreen());
			this->pixels[i][j].setBlue(this->maxValue - this->pixels[i][j].getBlue());
		}
	}
}


void PPM::rotation(std::string direction)
{
	if (direction == "left")
	{
		std::swap(this->width, this->height);
		
		std::vector<std::vector<RGB>> saver;
		for (int i = this->height - 1; i >= 0; i--)
		{
			std::vector<RGB> helper;
			for (int j = 0; j < this->width; j++)
			{
				helper.push_back(this->pixels[j][i]);		
			}
			saver.push_back(helper);
		}
		this->pixels = saver;
	}
	else if (direction == "right")
	{
		std::swap(this->width, this->height);

		std::vector<std::vector<RGB>> saver;
		for (int i = 0; i < this->height; i++)
		{
			std::vector<RGB> helper;
			for (int j = this->width - 1; j >= 0; j--)
			{
				helper.push_back(this->pixels[j][i]);
			}
			saver.push_back(helper);
		}
		this->pixels = saver;
	}
	else
	{
		std::cout << "Wrong direction!\n";
		return;
	}
}

void PPM::saveas(std::string path)
{
	std::ofstream saveas(path.c_str());
	saveas << this->ASCIInum << '\n';
	//std::cout << this->ASCIInum << '\n';
	//std::string comment = {};
	//std::streampos help = saveas.tellp();

	 //std::cout << "CHECK1\n";
	 saveas << this->comment << '\n';
	 //std::cout << this->comment[0]<<'\n';
	// std::cout << this->comment<<'\n';
	 
	//std::cout << "CHECK3\n";
	saveas << this->width << " " << this->height << '\n';
	//std::cout << "CHECK4\n";
	//std::cout << this->width << " " << this->height << '\n';

	saveas << this->maxValue << '\n';
	//std::cout << this->maxValue << '\n';
	
	for (int i = 0; i < this->height; i++)
	{
		for (size_t j = 0; j < this->width; j++)
		{
			saveas << this->pixels[i][j];
			//std::cout << this->pixels[i][j];
		}
		saveas << '\n';
		//std::cout << '\n';
	}

	saveas.close();
}

void PPM::collage(std::string direction, std::string image1, std::string image2, std::string outimage)
{
	std::vector<std::vector<RGB>> saver;
	PPM firstImage;
	firstImage.open(image1);
	
	PPM secondImage;
	secondImage.open(image2);
	
	if (firstImage.height == secondImage.height && firstImage.width == secondImage.width)
	{
		if (direction == "horizontal")
		{
			this->path = outimage;
			this->ASCIInum = firstImage.ASCIInum;
			this->comment = firstImage.comment + secondImage.comment;
			this->width = 2 * firstImage.width;
			this->height = firstImage.height;
			this->maxValue = (firstImage.maxValue + secondImage.maxValue) / 2;
			for (int i = 0; i < this->height; i++)
			{
				std::vector<RGB> helper;
				for (int j = 0; j < firstImage.width; j++)
				{
					helper.push_back(firstImage.pixels[i][j]);
				}

				for (int t = 0; t < secondImage.width; t++)
				{
					helper.push_back(secondImage.pixels[i][t]);
				}
				saver.push_back(helper);
			}
		}
		else if (direction == "vertical")
		{
			this->path = outimage;
			this->ASCIInum = firstImage.ASCIInum;
			this->width = firstImage.width;
			this->height = 2 * firstImage.height;
			this->maxValue = (firstImage.maxValue + secondImage.maxValue) / 2;

			size_t k = 0;
			for (int i = 0; i < this->height; i++)
			{
				std::vector<RGB> helper;
				if (i < firstImage.height)
				{
					for (int j = 0; j < firstImage.width; j++)
					{
						helper.push_back(firstImage.pixels[i][j]);
					}
				}
				else if (i >= firstImage.height)
				{
					for (size_t j = 0; j < this->width; j++)
					{
						helper.push_back(secondImage.pixels[k][j]);
					}
					k++;
				}
				saver.push_back(helper);
			}
		}
		else
		{
			std::cout << "Wrong direction!\n";
		}
		this->pixels = saver;
		this->saveas(outimage);
	}
	else
	{
		std::cout << "Unable to create collage!\n";
	}
}

void PPM::undoGrayscale()
{
	for (int i = 0; i < this->height; i++)
	{
		for (int j = 0; j < this->width; j++)
		{
			if ((this->pixels[i][j].getRed() != this->pixels[i][j].getGreen() || this->pixels[i][j].getRed() != this->pixels[i][j].getBlue()))
			{
				//Формула от tutorialspoint.com
				this->pixels[i][j].setRed(this->pixels[i][j].getRed()/0.3);
				this->pixels[i][j].setGreen(this->pixels[i][j].getGreen()/ 0.59);
				this->pixels[i][j].setBlue(this->pixels[i][j].getBlue()/ 0.11);
			}
		}
	}
}

void PPM::undoMonochrome()
{
	for (int i = 0; i < this->height; i++)
	{
		for (int j = 0; j < this->width; j++)
		{
			if (this->pixels[i][j].getRed() != this->pixels[i][j].getGreen() || this->pixels[i][j].getRed() != this->pixels[i][j].getBlue())
			{
				this->pixels[i][j].setRed(255);
				this->pixels[i][j].setGreen(255);
				this->pixels[i][j].setBlue(255);
			}
		}
	}
}

