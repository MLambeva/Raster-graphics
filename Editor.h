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
	Formats* loadAccordingToFormat(std::string path);//Връща обект към формата, който съответства на зададения адрес.
	bool isCommand(std::string command);//Проверява за коректност на командния ред.
	void help();//Извежда кратка информация за поддържаните от програмата команди.
	std::string findFormat(std::string path);//Връща разширението на файла.
	bool isCorrectFileExtension(std::string extension);//Проверява дали подаденото разширение се поддържа от програмата.
	std::vector<std::string> findPath(std::string paths);//Ако в един стринг има няколка адреса, т.е. няколко снимки, то тази функция ги отделя.	
	bool isCorrectFileFormat(std::string path);//Проверява по даден адрес дали е коректно разширението.
	void addEffectToPPM(Session& other, std::string effect);//Помощна функция за добавяне на трансформация в дадена сесия.
	bool read(std::string path);//Проверява дали състоянието на потока е добро.	

	//Функция, чрез която проверяваме дали при въвеждане на изображенията, има такова с валиден адрес, защото ако няма, то сесия без снимки е безсмислено.
	int countExistedImage(std::vector<std::string> path);
	
	//Основни команди.
	void commandGrayscale(Session& other);
	void commandMonochrome(Session& other);
	void commandNegative(Session& other);
	void commandSaveas(Session& other, std::string paths);
	void commandSave(Session& other);
	void commandAdd(Session& other, std::string paths);
	void commantRotation(Session& other);
	void commandSwitchSession();
	void commandUndo(Session& other);
	void commandCollage(Session& other);
	
	void load();//Командна функция, създаваща сесия и извършваща основните редакции по изображенията.

public:		
	void start();
};




#endif
