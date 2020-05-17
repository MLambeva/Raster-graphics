#ifndef FORMATS_H
#define FORMATS_H
#include<string>
#include<vector>

class Formats
{
protected:
	std::string path;
	std::string ASCIInum;
	std::string comment;
	int width;
	int height;

public:
	Formats() = default;
	Formats(std::string path, std::string ASCIInum, std::string comment, int width, int height);
	virtual ~Formats();

	std::string getPath() const;
	std::string getASCIInum() const;
	std::string getComment() const;
	int getWidth() const;
	int getHeight() const;

	void setWidth(int width);
	void setHeight(int height);

	virtual void print(std::ostream& out) const = 0;
	virtual void open(std::string path) = 0;
	virtual void saveas(std::string path) = 0;
	virtual void grayscale() = 0;
	virtual void monochrome() = 0;
	virtual void negative() = 0;
	virtual void rotation(std::string direction) = 0;
	virtual void collage(std::string direction, std::string image1, std::string image2, std::string outimage) = 0;

	virtual void undoGrayscale() = 0;
	virtual void undoMonochrome() = 0;
	
};

inline std::ostream& operator<<(std::ostream& out, const Formats& other)
{
	other.print(out);
	return out;
}



#endif
