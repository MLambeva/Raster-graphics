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

	static Formats* loadAccordingToFormat(std::string path);//����� ����� ��� �������, ����� ����������� �� ��������� �����.
	static bool isCommand(std::string command);//��������� �� ���������� �� ��������� ���.
	static void help();//������� ������ ���������� �� ������������ �� ���������� �������.
	static std::string findFormat(std::string path);//����� ������������ �� �����.
	static bool isCorrectFileExtension(std::string extension);//��������� ���� ���������� ���������� �� �������� �� ����������.
	static std::vector<std::string> findPath(std::string paths);//��� � ���� ������ ��� ������� ������, �.�. ������� ������, �� ���� ������� �� ������.	
	static bool isCorrectFileFormat(std::string path);//��������� �� ����� ����� ���� � �������� ������������.
	static void addEffectToPPM(Session& other, std::string effect);//������� ������� �� �������� �� ������������� � ������ �����.
	static bool read(std::string path);//��������� ���� ����������� �� ������ � �����.	

	//�������, ���� ����� ����������� ���� ��� ��������� �� �������������, ��� ������ � ������� �����, ������ ��� ����, �� ����� ��� ������ � �����������.
	static int countExistedImage(std::vector<std::string> path);
	
	//������� �������.
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
	
	static void load();//�������� �������, ��������� ����� � ���������� ��������� �������� �� �������������.

public:		
	static void start();
};




#endif
