#ifndef EDITOR_H
#define EDITOR_H
#include<string>
#include<vector>
#include<iostream>
#include"Session.h"
#include"PPM.h"
#include"PGM.h"
#include"PBM.h"

class Editor
{
private:
	static std::vector<Session> session;
	static std::string command;

	static Formats* loadAccordingToFormat(std::string path);//Връща обект към формата, който съответства на зададения адрес.
	static bool isCommand(std::string command);//Проверява за коректност на командния ред.
	static void help();//Извежда кратка информация за поддържаните от програмата команди.
	static std::string findFormat(std::string path);//Връща разширението на файла.
	static bool isCorrectFileExtension(std::string extension);//Проверява дали подаденото разширение се поддържа от програмата.
	static std::vector<std::string> findPath(std::string paths);//Ако в един стринг има няколка адреса, т.е. няколко снимки, то тази функция ги отделя.	
	static bool isCorrectFileFormat(std::string path);//Проверява по даден адрес дали е коректно разширението.
	static void addEffectToPPM(Session& other, std::string effect);//Помощна функция за добавяне на трансформация в дадена сесия.
	static bool read(std::string path);//Проверява дали състоянието на потока е добро.	

	//Функция, чрез която проверяваме дали при въвеждане на изображенията, има такова с валиден адрес, защото ако няма, то сесия без снимки е безсмислено.
	static int countExistedImage(std::vector<std::string> path);
	
	//Основни команди.
	static void commandGrayscale(Session& other);
	static void commandMonochrome(Session& other);
	static void commandNegative(Session& other);
	static void commandSaveas(Session& other, std::string paths);
	static void commandSave(Session& other);
	static void commandAdd(Session& other, std::string paths);
	static void commandRotation(Session& other);
	static void commandSwitchSession();
	static void commandUndo(Session& other);
	static void commandCollage(Session& other);
	
	static void load();//Командна функция, създаваща сесия и извършваща основните редакции по изображенията.

public:		
	static void start();
};




#endif
