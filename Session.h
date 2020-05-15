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
	std::vector<std::string> actions;
public:
	Session();
	Session(const Session& other);
	static int getId();
	std::vector<Formats*>& getFormats();
	std::vector<std::string> getActions();

	static int generateId();


	friend std::ostream& operator<<(std::ostream& out, const Session& other);


};


#endif
