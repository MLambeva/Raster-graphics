#include"PPM.h"
#include<cassert>


PPM::PPM() : Formats(), maxValue(0), pixels({ }) {};

PPM::~PPM()
{
}

void PPM::load(std::string path)//������� �� ��������� �� ���������� �� �����������.
{
	std::ifstream input(path.c_str());//����� �� ������.

	if (input.fail())//�������� �� ����������� �� ������.
	{
		std::cout << "Error!\n";
		return;
	}

	input >> this->ASCIInum;//���� ASCII ����.
	assert(this->ASCIInum == "P3");//�������� ���� � �������� ������ ������������ �� �����.
	
	this->path = path;//��������� ����� �� �����.
	
	//����� �� � �� ����� ���� ��� ����� ��� ��������, �� �� � ���� ����� �� �����.
	char x;
	input >> x;	
	if (x == '#')//����������� �������� � #.
	{
		input.unget();//����� get-��������� ���� ������ �����, �.�. ����� #.
		std::getline(input, this->comment);//������� ���������.
	}
	else//��� ���� ��������, �� ����� ������ �� �� ������� ���������� �� �������� � ����������.
	{
		input.unget();
	}
	
	input >> this->width;	
	input >> this->height;	
	input >> this->maxValue;

	int red, green, blue;
	for (int i = 0; i < this->height; i++)
	{
		std::vector<RGB> helper;//������� ����������, � ����� ��������� ��������� �� ����� ���.
		for (int j = 0; j < this->width; j++)
		{
			RGB saver;//� ���� ���������� ��������� ���� ������.
			input.ignore();
			input >> red >> green >> blue;	
			saver.setColor(red, green, blue);		
			helper.push_back(saver);//�������� ����� ������.			
		}
		this->pixels.push_back(helper);//������ ������� ����, �������� ��������� �� ����� ���.
	}	
	input.close();//��������� �����.
}

void PPM::saveas(std::string path) const//������� �� ��������� �� ���������� �� ����������� ��� ����, �������� �� ��������.
{
	std::ofstream saveas(path.c_str());//����� �� �����.

	saveas << this->ASCIInum << '\n';//��������� ASCII ����.
	saveas << this->comment << '\n';//��������� ���������.
	saveas << this->width << " " << this->height << '\n';//��������� ������ � ��������.
	saveas << this->maxValue << '\n';//��������� ������������ ��������.

	for (int i = 0; i < this->height; i++)
	{
		for (size_t j = 0; j < this->width; j++)
		{
			saveas << this->pixels[i][j];//��������� ����� ������.
		}
		saveas << '\n';
	}

	saveas.close();//��������� �����.
}

void PPM::print(std::ostream& out) const//������� �� ��������� �� ���������� �� ����� ������.
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

void PPM::grayscale()//������� ��������� �� �� � ��� �����.
{
	for (int i = 0; i < this->height; i++)
	{
		for (int j = 0; j < this->width; j++)
		{
			if ((this->pixels[i][j].getRed() != this->pixels[i][j].getGreen() || this->pixels[i][j].getRed() != this->pixels[i][j].getBlue()))
			{
				//������� �� tutorialspoint.com
				this->pixels[i][j].setColor(0.3 * this->pixels[i][j].getRed(), 0.59 * this->pixels[i][j].getGreen(), 0.11 * this->pixels[i][j].getBlue());
			}
		}
	}
}

void PPM::monochrome()//������� ��������� �� �� ����� ��� ����.
{
	(*this).grayscale();
	for (int i = 0; i < this->height; i++)
	{
		for (int j = 0; j < this->width; j++)
		{
			if (this->pixels[i][j].getRed() != this->pixels[i][j].getGreen() || this->pixels[i][j].getRed() != this->pixels[i][j].getBlue())
			{
				if (this->pixels[i][j].getRed() >= 123)
				{
					this->pixels[i][j].setColor(255,255,255);
				}
				else if (this->pixels[i][j].getRed() < 123)
				{
					this->pixels[i][j].setColor(0, 0, 0);
				}
			}
		}
	}
}

void PPM::negative()//������� ��������.
{
	for (int i = 0; i < this->height; i++)
	{
		for (int j = 0; j < this->width; j++)
		{
			this->pixels[i][j].setColor(this->maxValue - this->pixels[i][j].getRed(), 
			this->maxValue - this->pixels[i][j].getGreen(), this->maxValue - this->pixels[i][j].getBlue());
		}
	}
}


void PPM::rotation(std::string direction)//��������� �� ������������� �� 90� � ���������� �� ���������� ������.
{
	std::vector<std::vector<RGB>> saver;//������� ����������, � ����� ��������� ��������� �� ������ �����������.

	if (direction == "left")
	{
		std::swap(this->width, this->height);//��������� ����������� �� ���������� � ��������.		

		for (int i = this->height - 1; i >= 0; i--)
		{
			std::vector<RGB> helper;//������� ����������, � ����� ��������� ��������� �� ����� ���.
			for (int j = 0; j < this->width; j++)
			{
				helper.push_back(this->pixels[j][i]);		
			}
			saver.push_back(helper);
		}
	}
	else if (direction == "right")
	{
		std::swap(this->width, this->height);

		for (int i = 0; i < this->height; i++)
		{
			std::vector<RGB> helper;//������� ����������, � ����� ��������� ��������� �� ����� ���.
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
	this->pixels = saver;//����������� ����������� �� ���������.
}

void PPM::collage(std::string direction, std::string image1, std::string image2, std::string outimage)
{
	/*��������� �� ����� �� ��� ����������� (<image1>, <image2>), ����� �� �� ���� � ��� ������ � ������� ���������� � ���������� �� �������� ������ -
	������������ ��� ����������, ���� ���������� ����������� �� ������� � ���� ����������� <outimage>*/
	std::vector<std::vector<RGB>> saver;//������� ����������, � ����� ��������� ��������� �� ������ �����������.

	PPM firstImage;//����� �� ������� ����, � ����� �� ����������� ������� �� ������� �����������.
	firstImage.load(image1);
	
	PPM secondImage;//����� �� ������� ����, � ����� �� ����������� ������� �� ������� �����������.
	secondImage.load(image2);
	
	if (firstImage.height == secondImage.height && firstImage.width == secondImage.width)//�������, ����� ������ �� ����������.
	{
		if (direction == "horizontal")
		{
			this->path = outimage;
			this->ASCIInum = firstImage.ASCIInum;//ASCII �������� �� 2�� ����������� ��������, ������ �� �� ���� ������.
			this->comment = firstImage.comment + secondImage.comment;//������������ �� ����� ���������.
			this->width = 2 * firstImage.width;//�������� �� ��������� ��� ����.
			this->height = firstImage.height;//���������� ������ ������.
			this->maxValue = (firstImage.maxValue + secondImage.maxValue) / 2;//������������ �������� � ����������������� �� �����.
			for (int i = 0; i < this->height; i++)
			{
				std::vector<RGB> helper;//������� ����������, � ����� ��������� ��������� �� ����� ���.
				for (int j = 0; j < firstImage.width; j++)//����� ��������� ���� �� ������� �����������.
				{
					helper.push_back(firstImage.pixels[i][j]);//�������� �����������.
				}
				for (int t = 0; t < secondImage.width; t++)//���� ���� ��������� ���� �� ������� �����������.
				{
					helper.push_back(secondImage.pixels[i][t]);//�������� �����������.
				}
				saver.push_back(helper);//���� ����������� �� ����� ���, �������� ����������� � ��������� ����������.
			}
		}
		else if (direction == "vertical")
		{
			this->path = outimage;
			this->ASCIInum = firstImage.ASCIInum;//ASCII �������� �� 2�� ����������� ��������, ������ �� �� ���� ������.
			this->comment = firstImage.comment + secondImage.comment;//������������ �� ����� ���������.
			this->width = firstImage.width;//�������� ������ ������.
			this->height = 2 * firstImage.height;//���������� �� ��������� ��� ����.
			this->maxValue = (firstImage.maxValue + secondImage.maxValue) / 2;//������������ �������� � ����������������� �� �����.

			//��������� ������ ������ �� ������� �����������, � ���� ���� ������ ������ �� �������.
			size_t k = 0;//������ �� ������������ ����� ��� ��������� �� ������� �����������.
			for (int i = 0; i < this->height; i++)
			{
				std::vector<RGB> helper;//������� ����������, � ����� ��������� ��������� �� ����� ���.
				if (i < firstImage.height)
				{
					//��������� �� ����� �����������.
					for (int j = 0; j < firstImage.width; j++)
					{
						helper.push_back(firstImage.pixels[i][j]);
					}
				}
				else if (i >= firstImage.height)
				{
					//��������� �� ����� �����������.
					for (size_t j = 0; j < this->width; j++)
					{
						helper.push_back(secondImage.pixels[k][j]);
					}
					k++;//����������� ������, �.�. ����������� �� ��������� ���.
				}
				saver.push_back(helper);//���� ����������� �� ����� ���, �������� ����������� � ��������� ����������.
			}
		}
		else
		{
			std::cout << "Wrong direction!\n";
		}
		this->pixels = saver;//����������� ����������� �� ���������.
		this->saveas(outimage);//��������� ���������� �����������.
	}
	else
	{
		std::cout << "Unable to create collage!\n";
	}
}

void PPM::undoGrayscale()//������� �� ���������� �� ���� ������.
{
	for (int i = 0; i < this->height; i++)
	{
		for (int j = 0; j < this->width; j++)
		{
			if ((this->pixels[i][j].getRed() != this->pixels[i][j].getGreen() || this->pixels[i][j].getRed() != this->pixels[i][j].getBlue()))
			{
				//������� �� tutorialspoint.com
				this->pixels[i][j].setRed(this->pixels[i][j].getRed()/0.3);
				this->pixels[i][j].setGreen(this->pixels[i][j].getGreen()/ 0.59);
				this->pixels[i][j].setBlue(this->pixels[i][j].getBlue()/ 0.11);
			}
		}
	}
}

void PPM::undoMonochrome()//������� �� ���������� �� �����/���� ������.
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

