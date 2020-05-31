#ifndef SESSION_H
#define SESSION_H
#include<vector>
#include<string>
#include<iostream>
#include"Formats.h"

class Session
{
private:
	static int id;
	std::vector<Formats*> formats;
	std::vector<std::string> transformations;
public:
	Session();
	
	static int getId();
	std::vector<Formats*>& Formats();
	std::vector<std::string>& Transformations();
		
	void addTransformations(std::string transformations);//������� �������� �� �������� �� �������������.

	static int generateId();//�������� ����������������� �����.

	friend std::ostream& operator<<(std::ostream& out, const Session& other);

};


#endif
