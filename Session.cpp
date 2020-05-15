#include"Session.h"


int Session::id = 0;

Session::Session()
{
	this->id = Session::generateId();
	for (size_t i = 0; i < this->formats.size(); i++)
	{
		this->formats[i] = nullptr;
	}
	for (size_t i = 0; i < this->actions.size(); i++)
	{
		this->actions[i] = nullptr;
	}
}

Session ::Session(const Session& other)
{
	this->id = other.id;
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

std::vector<std::string> Session::getActions()
{
	return this->actions;
}

int Session::generateId()
{
	return ++id;
}

std::ostream& operator<<(std::ostream& out, const Session& other)
{
	out << "Session ID: " << other.id << '\n';
	for (size_t i = 0; i < other.formats.size(); i++)
	{
		out << *other.formats[i] << " ";
	}
	for (size_t i = 0; i < other.actions.size(); i++)
	{
		out << other.actions[i] << " ";
	}
	
	return out;
}