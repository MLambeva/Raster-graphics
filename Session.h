#ifndef SESSION_H
#define SESSION_H
#include<vector>
#include<iostream>
#include"Formats.h"

class Session
{
private:
	static int id;
	std::vector<Formats*> formats;
	std::vector<std::string> path;
public:
	Session();
	Session(const Session& other);
	static int getId();
	std::vector<Formats*>& getFormats();
	std::vector<std::string> getPath();
	static int generateId();

	void setPath(std::vector<std::string>);
	void addPath(const std::string& path);

	friend std::ostream& operator<<(std::ostream& out, const Session& other);


};


#endif
