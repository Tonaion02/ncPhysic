#pragma once

#include <string>





//Pixel container
struct StaticPixel
{
	StaticPixel(){}
	StaticPixel(uint32_t r, uint32_t g, uint32_t b, uint32_t a);

	uint32_t operator[](int index) const;

	uint32_t r, g, b, a;
};
//Pixel container





//StaticImage Class
class StaticImage
{
public:
	//Constructor

	StaticImage() {}
	StaticImage(const std::string& fileName, unsigned int comp = 4);
	StaticImage(int width, int height, const StaticPixel& pixel = {0, 0, 0, 0}, unsigned int comp = 4);
	//Constructor

	void setPixel(int index, const StaticPixel& pix) 
	{ 
		p[index] = pix.r;
		p[index + 1] = pix.g; 
		p[index + 2] = pix.b;
		p[index + 3] = pix.a;
	}

	void setPixel(int x, int y, const StaticPixel& pix)
	{

	}

	StaticPixel getPixel(int x, int y) const;

	bool blit(int x, int y, const StaticImage& img);
	bool blitSobstitude(int x, int y, const StaticImage& img);
	bool blitColorOver(int x, int y, const StaticImage& img);

	void save();

	void setFileName(const std::string& name) { fileName = name; }

	//Info about StaticImage
	int getWidth() const { return width; }
	int getHeight() const { return height; }
	std::string getFileName() const { return fileName; }
	//Info about StaticImage



private:
	int width, height;
	int bpp;

	unsigned char* p;

	std::string fileName;
};
//StaticImage Class