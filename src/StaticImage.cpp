#include "StaticImage.h"

#include <cassert>
#include <algorithm>

#include "vendor/stbi_image/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "vendor/stbi_image/stb_image_write.h"





//Pixel container

//Pixel constructor
StaticPixel::StaticPixel(uint32_t r, uint32_t g, uint32_t b, uint32_t a)
	: r(r), g(g), b(b), a(a)
{

}
//Pixel constructor

//Pixel Operator
uint32_t StaticPixel::operator[](int index) const
{
	assert(index >= 0 && index <= 4);

	switch (index)
	{
	case 0:
		return r;
	case 1:
		return b;
	case 2:
		return g;
	case 3:
		return a;
	}
}
//Pixel Operator

//Pixel container





//Class StaticImage

//StaticImage Constructor
StaticImage::StaticImage(const std::string& fileName, unsigned int comp)
	:fileName(fileName), width(0), height(0), bpp(0)
{
	assert(fileName.size() > 0 && comp > 0);

	p = stbi_load(fileName.c_str(), &width, &height, &bpp, comp);

	assert(p != nullptr);
}

StaticImage::StaticImage(int width, int height, const StaticPixel& pixel, unsigned int comp)
	:width(width), height(height), bpp(comp)
{
	assert(width > 0 && height > 0 && comp > 0);

	p = new unsigned char[width * height * comp];
	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			for (int b = 0; b < bpp; b++)
			{
				p[(j * width * bpp) + (i * bpp) + b] = pixel[b];
			}
		}
	}

}
//StaticImage Constructor

//Blits color of Image
bool StaticImage::blit(int x, int y, const StaticImage& img)
{
	if (x < 0 && x > width && y < 0 && y > height)
		return false;

	int mX = img.getWidth();
	int mY = img.getHeight();

	if (img.getWidth() >= getWidth())
		mX = getWidth() - x;
	if (img.getHeight() >= getHeight())
		mY = getHeight() - y;

	for (int j = 0; j < mY; j++)
	{
		for (int i = 0; i < mX; i++)
		{
			StaticPixel pO = getPixel(i, j);
			StaticPixel pN = img.getPixel(i, j);

			if (pN.a >= pO.a)
				setPixel(((y + j) * getWidth() * bpp) + ((i + x) * bpp), pN);
			else
				setPixel(((y + j) * getWidth() * bpp) + ((i + x) * bpp), pO);
		}
	}

	return true;
}
//Blits color of Image

//Blit an Image onto current Image
bool StaticImage::blitSobstitude(int x, int y, const StaticImage& img)
{
	//assert(x >= 0 && x < getWidth() && y >= 0 && y < getHeight());

	if (x < 0 && x > width && y < 0 && y > height)
		return false;

	int mX = img.getWidth();
	int mY = img.getHeight();

	if (img.getWidth() >= getWidth())
		mX = getWidth() - x;
	if (img.getHeight() >= getHeight())
		mY = getHeight() - y;

	for (int j = 0; j < mY; j++)
	{
		for (int i = 0; i < mX; i++)
		{
			setPixel(((y + j) * getWidth() * bpp) + ((i + x) * bpp), img.getPixel(i, j));
		}
	}

	return true;
}
//Blit an Image onto current Image

//Intermediate the color of image
bool StaticImage::blitColorOver(int x, int y, const StaticImage& img)
{
	//assert(x >= 0 && x < getWidth() && y >= 0 && y < getHeight());

	if (x < 0 && x > width && y < 0 && y > height)
		return false;

	int mX = img.getWidth();
	int mY = img.getHeight();

	if (img.getWidth() >= getWidth())
		mX = getWidth() - x;
	if (img.getHeight() >= getHeight())
		mY = getHeight() - y;

	for (int j = 0; j < mY; j++)
	{
		for (int i = 0; i < mX; i++)
		{
			StaticPixel pO = getPixel(i, j);
			StaticPixel pN = img.getPixel(i, j);
			StaticPixel pR;

			int divAlpha = pO.a + pN.a * (255 - pO.a);
			if (divAlpha == 0)
				divAlpha = 1;
			pR.r = ((pO.r * pO.a) + (pN.r * pN.a)*(255 - pO.a)) / divAlpha;
			pR.r = ((pO.g * pO.a) + (pN.g * pN.a)*(255 - pO.a)) / divAlpha;
			pR.r = ((pO.b * pO.a) + (pN.b * pN.a)*(255 - pO.a)) / divAlpha;
			pR.a = 255 * ((pO.a / 255) + (pN.a / 255)*(255 / 255 - pO.a / 255));

			setPixel(((y + j) * getWidth() * bpp) + ((i + x) * bpp), pR);
		}
	}

	return true;
}
//Intermediate the color of image

//Get and Set Pixel of StaticImage
StaticPixel StaticImage::getPixel(int x, int y) const
{
	assert(x >= 0 && x < getWidth() && y >= 0 && getHeight());

	int index = (y * width * bpp) + (x * bpp);
	return StaticPixel(p[index], p[index + 1], p[index + 2], p[index + 3]);
}
//Get and Set Pixel of StaticImage

//Save changes on StaticImage
void StaticImage::save()
{
	assert(fileName.size() > 0);
	
	stbi_write_png(fileName.c_str(), width, height, STBI_rgb_alpha, p, width * STBI_rgb_alpha);
}
//Save changes on StaticImage

//Class StaticImage