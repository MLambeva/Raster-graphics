#ifndef FORMATS_H
#define FORMATS_H
#include<string>

class Formats
{
protected:
	std::string ASCIInum;
	int width;
	int height;

public:
	Formats() = default;
	Formats(std::string ASCIInum, int width, int height);
	virtual ~Formats();

	std::string getASCIInum() const;
	int getWidth() const;
	int getHeight() const;

	void setWidth(int width);
	void setHeight(int height);

	virtual void print(std::ostream& out) const = 0;
	virtual void load(std::string path) = 0;
	
	
};

inline std::ostream& operator<<(std::ostream& out, const Formats& other)
{
	other.print(out);
	return out;
}


#endif
