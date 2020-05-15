#ifndef HELPER_FUNCTIONS_H
#define HELPER_FUNCTIONS_H
#include<string>
#include<vector>
#include<fstream>

class helperFunctions
{
public:
	static std::string findFormat(std::string path);
	static std::vector<std::string> findPath(std::string paths);
	static bool isCorrectFileFormat(std::string path);
	static bool read(std::string path);
	
};





#endif