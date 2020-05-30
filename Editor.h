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
	Formats* loadAccordingToFormat(std::string path);//����� ����� ��� �������, ����� ����������� �� ��������� �����.
	bool isCommand(std::string command);//��������� �� ���������� �� ��������� ���.
	void help();//������� ������ ���������� �� ������������ �� ���������� �������.
	std::string findFormat(std::string path);//����� ������������ �� �����.
	bool isCorrectFileExtension(std::string extension);//��������� ���� ���������� ���������� �� �������� �� ����������.
	std::vector<std::string> findPath(std::string paths);//��� � ���� ������ ��� ������� ������, �.�. ������� ������, �� ���� ������� �� ������.	
	bool isCorrectFileFormat(std::string path);//��������� �� ����� ����� ���� � �������� ������������.
	void addEffectToPPM(Session& other, std::string effect);//������� ������� �� �������� �� ������������� � ������ �����.
	bool read(std::string path);//��������� ���� ����������� �� ������ � �����.	

	//�������, ���� ����� ����������� ���� ��� ��������� �� �������������, ��� ������ � ������� �����, ������ ��� ����, �� ����� ��� ������ � �����������.
	int countExistedImage(std::vector<std::string> path);
	
	//������� �������.
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
	
	void load();//�������� �������, ��������� ����� � ���������� ��������� �������� �� �������������.

public:		
	void start();
};




#endif
