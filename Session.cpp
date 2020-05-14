#include"Session.h"


int Session::id = 0;

Session::Session()
{
	this->id = Session::generateId();
	for (int i = 0; i < this->formats.size(); i++)
	{
		this->formats[i] = nullptr;
	}
	for (int i = 0; i < this->path.size(); i++)
	{
		this->path[i] = nullptr;
	}
}

Session ::Session(const Session& other)
{
	this->id = other.id;
	this->formats = other.formats;
	this->formats = other.formats;
}

int Session::getId()
{
	return id;
}

std::vector<Formats*>& Session::getFormats()
{
	return this->formats;
}

std::vector<std::string> Session::getPath()
{
	return this->path;
}

int Session::generateId()
{
	return ++id;
}

void Session::setPath(std::vector<std::string>)
{
	this->path = path;
}

void Session::addPath(const std::string& path)
{
	this->path.push_back(path);
}

std::ostream& operator<<(std::ostream& out, const Session& other)
{
	out << "Session ID: " << other.id << '\n';
	for (int i = 0; i < other.path.size(); i++)
	{
		out << "Path: " << other.path[i] << '\n';
	}
	for (int i = 0; i < other.formats.size(); i++)
	{
		out << *other.formats[i] << " ";
	}
	
	return out;
}