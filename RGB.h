#ifndef RGB_H
#define RGB_H
#include<string>
#include<iostream>

class RGB 
{
private:
	int red;
	int green;
	int blue;
public:
	RGB() :red(0), green(0), blue(0) {};

	int getRed() const;
	int getGreen() const;
	int getBlue() const;

	RGB setColor(int red, int green, int blue);

	void setRed(const int &red);
	void setGreen(const int &green);
	void setBlue(const int &blue);

	friend std::ostream& operator << (std::ostream& out, const RGB& other);
};


#endif