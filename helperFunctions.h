#ifndef HELPER_FUNCTIONS_H
#define HELPER_FUNCTIONS_H
#include<string>
#include<vector>
#include<fstream>
#include<iostream>
#include "Session.h"
#include"Formats.h"

class helperFunctions
{
public:
	static std::string findFormat(std::string path);
	static std::vector<std::string> findPath(std::string paths);
	static bool isCorrectFileExtension(std::string extension);
	static bool isCorrectFileFormat(std::string path);
	static bool read(std::string path);
	static bool isOneDigit(int x);
	static bool isTwoDigit(int x);
	static bool isThreeDigit(int x);
	static bool isCommand(std::string command);
	static void help();
	


};





#endif