#include"PPM.h"
#include<cassert>


PPM::PPM() : Formats(), maxValue(0), pixels({ }) {};

PPM::PPM(std::string ASCIInum, std::string path, int width, int height, int maxValue, std::vector<std::vector<RGB>>pixels)
	:Formats(ASCIInum, path, width, height)
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
		this->ASCIInum = other.ASCIInum;
		this->path = other.path;
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

	std::string ASCIInum;
	input >> ASCIInum;
	if (ASCIInum != "P3")//Няма смисъл, когато направя и за другите формати. 
	{
		input.close();
		return;
	}
	this->ASCIInum = ASCIInum;
	this->path = path;
	
	int width;
	int height;
	int maxValue;
	input >> width;
	input >> height;
	input >> maxValue;

	this->width = width;
	this->height = height;
	this->maxValue = maxValue;	
	
	int red, green, blue;
	for (int i = 0; i < this->height; i++)
	{
		std::vector<RGB> helper;
		for (int j = 0; j < this->width; j++)
		{
			RGB saver;
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
	out << "ASCII number: " << this->ASCIInum << '\n';
	out << this->path << '\n';
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
			this->pixels[i][j].setRed(255 - this->pixels[i][j].getRed());
			this->pixels[i][j].setGreen(255 - this->pixels[i][j].getGreen());
			this->pixels[i][j].setBlue(255 - this->pixels[i][j].getBlue());
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

void PPM::save(std::string path)
{
	std::ofstream save(path.c_str());
	//this->ASCIInum = "P3";
	save << this->ASCIInum << '\n';
	//std::cout << this->ASCIInum << '\n';
	save << this->width << " " << this->height << '\n';
	//std::cout << this->width << " " << this->height << '\n';
	//this->maxValue = 255;
	save << this->maxValue << '\n';
	//std::cout << this->maxValue << '\n';
	
	for (int i = 0; i < this->height; i++)
	{
		for (size_t j = 0; j < this->width; j++)
		{
			save << this->pixels[i][j];
			//std::cout << this->pixels[i][j];
		}
		save << '\n';
		//std::cout << '\n';
	}

	save.close();
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

