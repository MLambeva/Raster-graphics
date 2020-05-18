#include"PBM.h"

PBM::PBM():Formats()
{
	this->pixels = { };
};

PBM::~PBM()
{
}

void PBM::load(std::string path)//������� �� ��������� �� ���������� �� �����������.
{
	std::ifstream input(path.c_str());//����� �� ������.

	if (input.fail())//�������� �� ����������� �� ������.
	{
		std::cout << "Error!\n";
		return;
	}
	
	input >> this->ASCIInum;//���� ASCII ����.
	assert(this->ASCIInum == "P1");//�������� ���� � �������� ������ ������������ �� �����.
	
	this->path = path;//��������� ����� �� �����.

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
	
	for (int i = 0; i < this->height; i++)
	{
		int x;
		std::vector<int> helper;//������� ����������, � ����� ��������� ��������� �� ����� ���.	
		for (int j = 0; j < this->width; j++)
		{
			input >> x;//����� ����� ������.
			assert(x == 0 || x == 1);
			helper.push_back(x);//�������� ����� ������.
		}
		this->pixels.push_back(helper);//������ ������� ����, �������� ��������� �� ����� ���.
	}	
	input.close();//��������� �����.
}

void PBM::saveas(std::string path) const//������� �� ��������� �� ���������� �� ����������� ��� ����, �������� �� ��������.
{
	std::ofstream saveas(path.c_str());//����� �� �����.

	saveas << this->ASCIInum << '\n';//��������� ASCII ����.
	saveas << this->comment << '\n';//��������� ���������.
	saveas << this->width << " " << this->height << '\n';//��������� ������ � ��������.

	for (int i = 0; i < this->height; i++)
	{
		for (int j = 0; j < this->width; j++)
		{
			assert(this->pixels[i][j] == 0 || this->pixels[i][j] == 1);
			saveas << this->pixels[i][j];//��������� ����� ������.
		}
		saveas << '\n';
	}

	saveas.close();//��������� �����.
}

void PBM::print(std::ostream& out) const//������� �� ��������� �� ���������� �� ����� ������.
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

void PBM::grayscale() {}//�������, ����� �� ����� ������� ����� �������������, ������ �� � �����-����.

void PBM::monochrome() {}//�������, ����� �� ����� ������� ����� �������������, ������ �� � �����-����.

void PBM::negative() //������� ��������.
{
	for (int i = 0; i < this->height; i++)
	{
		for (int j = 0; j < this->width; j++)
		{
			this->pixels[i][j] = 1 - this->pixels[i][j];
		}
	}
}

void PBM::rotation(std::string direction) //��������� �� ������������� �� 90� � ���������� �� ���������� ������.
{
	std::vector<std::vector<int>> saver;//������� ����������, � ����� ��������� ��������� �� ������ �����������.

	if (direction == "left")
	{
		std::swap(this->width, this->height);//��������� ����������� �� ���������� � ��������.		
				
		for (int i = this->height - 1; i >= 0; i--)
		{
			std::vector<int> helper;//������� ����������, � ����� ��������� ��������� �� ����� ���.
			for (int j = 0; j < this->width; j++)
			{
				helper.push_back(this->pixels[j][i]);
			}
			saver.push_back(helper);
		}
		
	}
	else if (direction == "right")
	{
		std::swap(this->width, this->height);//��������� ����������� �� ���������� � ��������.		

		for (int i = 0; i < this->height; i++)
		{
			std::vector<int> helper;//������� ����������, � ����� ��������� ��������� �� ����� ���.
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

void PBM::collage(std::string direction, std::string image1, std::string image2, std::string outimage) 
{
	/*��������� �� ����� �� ��� ����������� (<image1>, <image2>), ����� �� �� ���� � ��� ������ � ������� ���������� � ���������� �� �������� ������ -
	������������ ��� ����������, ���� ���������� ����������� �� ������� � ���� ����������� <outimage>*/
	std::vector<std::vector<int>> saver;//������� ����������, � ����� ��������� ��������� �� ������ �����������.

	PBM firstImage;//����� �� ������� ����, � ����� �� ����������� ������� �� ������� �����������.
	firstImage.load(image1);

	PBM secondImage;//����� �� ������� ����, � ����� �� ����������� ������� �� ������� �����������.
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
			for (int i = 0; i < this->height; i++)
			{
				std::vector<int> helper;//������� ����������, � ����� ��������� ��������� �� ����� ���.
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
			
			//��������� ������ ������ �� ������� �����������, � ���� ���� ������ ������ �� �������.
			size_t k = 0;//������ �� ������������ ����� ��� ��������� �� ������� �����������.
			for (int i = 0; i < this->height; i++)
			{
				std::vector<int> helper;//������� ����������, � ����� ��������� ��������� �� ����� ���.
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

void PBM::undoGrayscale() {}//�������, ����� �� ����� ������� ����� �������������, ������ �� � �����-����.

void PBM::undoMonochrome() {}//�������, ����� �� ����� ������� ����� �������������, ������ �� � �����-����.