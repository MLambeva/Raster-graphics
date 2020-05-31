#include"Session.h"


int Session::id = 0;//�������� ���� �����, ����� �� ������� ���� ������� �� 0.

Session::Session()
{
	this->id = Session::generateId();//������������������ ����� �� �������� ��� ����� ���������� �� ������������.
	for (size_t i = 0; i < this->formats.size(); i++)
	{
		this->formats[i] = nullptr;
	}
	for (size_t i = 0; i < this->transformations.size(); i++)
	{
		this->transformations[i] = nullptr;
	}
}

int Session::getId()
{
	return id;
}

std::vector<Formats*>& Session::Formats()
{
	return this->formats;
}

std::vector<std::string>& Session::Transformations()
{
	return this->transformations;
}

void Session::addTransformations(std::string transformations)//������� �������� �� �������� �� �������������.
{
	this->transformations.push_back(transformations);
}

int Session::generateId()//�������� ����������������� �����.
{
	return ++id;
}

std::ostream& operator<<(std::ostream& out, const Session& other)
{
	out << "Session ID: " << other.id << '\n';//�������� ����������������� ����� �� �������.
	out << "Name of images in the session: ";
	for (size_t i = 0; i < other.formats.size(); i++)
	{
		out << other.formats[i]->getPath() << ", ";//������� ������� �� �������������, ����� �� � �������.
	}
	out << '\n';
	out << "Pending transformations: ";
	for (size_t i = 0; i < other.transformations.size(); i++)
	{
		out << other.transformations[i] << ", ";//������� ���������, ����� �� ��������� ����� �������������.
	}
	
	return out;
}