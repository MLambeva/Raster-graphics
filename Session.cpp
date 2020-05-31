#include"Session.h"


int Session::id = 0;//Статична член данна, която се променя като започва от 0.

Session::Session()
{
	this->id = Session::generateId();//Идентификационният номер се генерира при всяко използване на конструктура.
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

void Session::addTransformations(std::string transformations)//Помощна функциия за добавяне на трансформация.
{
	this->transformations.push_back(transformations);
}

int Session::generateId()//Генерира идентификационния номер.
{
	return ++id;
}

std::ostream& operator<<(std::ostream& out, const Session& other)
{
	out << "Session ID: " << other.id << '\n';//Принтира идентификационния номер на сесията.
	out << "Name of images in the session: ";
	for (size_t i = 0; i < other.formats.size(); i++)
	{
		out << other.formats[i]->getPath() << ", ";//Извежда имената на изображенията, които са в сесията.
	}
	out << '\n';
	out << "Pending transformations: ";
	for (size_t i = 0; i < other.transformations.size(); i++)
	{
		out << other.transformations[i] << ", ";//Извежда промените, които са настъпили върху изображението.
	}
	
	return out;
}