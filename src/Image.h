#pragma once

#include "PrecompiledHeaders.h"

#include <nctl/UniquePtr.h>
#include <nctl/SharedPtr.h>

#include <ncine/SceneNode.h>
#include <ncine/Texture.h>
#include <ncine/Sprite.h>





namespace nc = ncine;

class TextureLoader
{
public:
	TextureLoader() {}

	static void loadTexture(const std::string& fileName);
	static nc::Texture* getTexture(const std::string& fileName);

private:
	static std::vector<std::string> fileNameTextures;
	static std::vector<nctl::UniquePtr<nc::Texture>> textures;
};

class Image
{
public:
	Image(){}
	Image(nc::Texture* texture);
	Image(nc::Texture* texture, nc::SceneNode* scene);

	void draw(int layer=0);
	void draw(const nc::Vector2i& pos, int layer=0);
	void draw(int x, int y,int layer=0);
	void draw(const nc::Vector2i pos, const nc::Vector2i min, const nc::Vector2i dimension, int layer);
	void draw(int x, int y, int xi, int yi, int w, int h, int layer = 0);

	void setAlpha(float alpha);

	int getWidth() const { return m_Sprite->width(); }
	int getHeight() const { return m_Sprite->height(); }

	int getLayer() const { return m_Sprite->layer(); }

	void destroy();

	void resetCondition() { m_Sprite->setDrawEnabled(false); }
	static void resetAllCondition();

	void setScale(float scaleX, float scaleY) { m_Sprite->setScale(scaleX, scaleY); }
	static void setBasicScene(nc::SceneNode* scene) { s_BasicScene = scene; }

private:
	//nctl::UniquePtr<nc::Sprite> m_Sprite;
	nctl::SharedPtr<nc::Sprite> m_Sprite;

	static nc::SceneNode* s_BasicScene;
	static std::vector<Image*> s_BufferImage;
};
