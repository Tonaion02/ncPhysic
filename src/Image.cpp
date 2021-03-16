#include "Image.h"





//Class TextureLoader

std::vector<std::string> TextureLoader::fileNameTextures;
std::vector<nctl::UniquePtr<nc::Texture>> TextureLoader::textures;

void TextureLoader::loadTexture(const std::string& fileName)
{
	bool loaded = false;
	for (int i = 0; i < fileNameTextures.size(); i++)
	{
		if (fileNameTextures[i] == fileName)
		{
			loaded = true;
		}
	}

	if (!loaded)
	{
		fileNameTextures.push_back(fileName);
		textures.push_back(nctl::makeUnique<nc::Texture>(fileName.c_str()));
	}
}

nc::Texture* TextureLoader::getTexture(const std::string& fileName)
{
	for (int i = 0; i < fileNameTextures.size(); i++)
	{
		if (fileNameTextures[i] == fileName)
		{
			return textures[i].get();
		}
	}

	assert(false);
}

//Class TextureLoader





//Class Image

nc::SceneNode* Image::s_BasicScene = nullptr;
std::vector<Image*> Image::s_BufferImage;

//Image constructor
Image::Image(nc::Texture* texture)
	:m_Sprite(nctl::makeShared<nc::Sprite>(s_BasicScene, texture))
{
	//m_Sprite = nctl::makeUnique<nc::Sprite>(s_BasicScene, texture);
	m_Sprite->setDrawEnabled(false);
}

Image::Image(nc::Texture* texture, nc::SceneNode* scene)
	:m_Sprite(nctl::makeShared<nc::Sprite>(scene, texture))
{
	//m_Sprite = nctl::makeUnique<nc::Sprite>(scene, texture);
	m_Sprite->setDrawEnabled(false);
}
//Image constructor

//Image Draw
void Image::draw(int layer)
{
	m_Sprite->setDrawEnabled(true);
	m_Sprite->setLayer(layer);

	s_BufferImage.push_back(this);
}

void Image::draw(const nc::Vector2i& pos, int layer)
{
	m_Sprite->setDrawEnabled(true);
	m_Sprite->setLayer(layer);
	m_Sprite->setPosition(nc::Vector2f(pos.x, pos.y));

	s_BufferImage.push_back(this);
}

void Image::draw(int x, int y, int layer)
{
	m_Sprite->setDrawEnabled(true);
	m_Sprite->setPosition(x, y);
	m_Sprite->setLayer(layer);

	s_BufferImage.push_back(this);
}

//void Image::draw(int x, int y, int w, int h, int layer)
//{
//	m_Sprite->setDrawEnabled(true);
//	//m_Sprite->setPosition(x + w/2, y + h/2);
//	m_Sprite->setPosition(x, y);
//	m_Sprite->setTexRect(nc::Recti(x, y, w, h));
//	m_Sprite->setLayer(layer);
//
//	s_BufferImage.push_back(this);
//}

void Image::draw(const nc::Vector2i pos, const nc::Vector2i min, const nc::Vector2i dimension, int layer)
{
	m_Sprite->setDrawEnabled(true);
	m_Sprite->setTexRect(nc::Recti(min.x, min.y, dimension.x, dimension.y));
	m_Sprite->setPosition(nc::Vector2f(pos.x, pos.y));
	m_Sprite->setLayer(layer);
	
	s_BufferImage.push_back(this);
}

void Image::draw(int x, int y, int xi, int yi, int w, int h, int layer)
{
	m_Sprite->setDrawEnabled(true);
	m_Sprite->setTexRect(nc::Recti(xi, yi, w, h));
	m_Sprite->setPosition(x, y);
	m_Sprite->setLayer(layer);

	s_BufferImage.push_back(this);
}
//Image Draw

//Image Reset Condition
void Image::resetAllCondition()
{
	for (auto* i : s_BufferImage)
	{
		i->resetCondition();
	}

	s_BufferImage.clear();
}
//Image Reset Condition

//Class Image