#include "Renderer/Renderer.h"





//Class Renderer

DebugLayer Renderer::debugLayer;

uint32_t Renderer::maxLayer;
std::vector<nc::SceneNode*> Renderer::Layer;

//Renderer Constructor
Renderer::Renderer(uint32_t maxZ)
{
	Layer.clear();
	for (int i = 0; i < maxZ; i++)
	{
		Layer.push_back(new nc::SceneNode());
	}

	maxLayer = maxZ;
}
//Renderer Constructor

//Renderer DebugLayer Construction

void Renderer::constructDebugLayer(const std::string& fileNameFontTxt, const std::string& fileNameFontPng)
{
	debugLayer = DebugLayer(fileNameFontTxt, fileNameFontPng);
}

//Renderer DebugLayer Construction

//Renderer attach layer
void Renderer::attachLayer()
{
	for (int i = 0; i < maxLayer;i++)
	{
		nc::theApplication().rootNode().addChildNode(Layer[i]);
	}
}
//Renderer attach layer

//Disable Layers
void Renderer::setEnableLayer(uint32_t layer, bool enable)
{
	Layer[layer]->setDrawEnabled(enable);
}
//Disable Layers

//Clear the layers
void Renderer::clearLayer()
{
	for (int i = 0; i < Layer.size(); i++)
	{
		delete Layer[i];
	}
}
//Clear the layers

//Clear the screen
void Renderer::clearScreen(const nc::Color& color)
{
	nc::theApplication().gfxDevice().setClearColor((nc::Colorf)color);
}
//Clear the screen

//Class Renderer