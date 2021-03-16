#pragma once

#include "PrecompiledHeaders.h"

#include "Options.h"

#include "Image.h"

#include "DebugLayer.h"

#include <ncine/Application.h>





class Renderer
{
public:
	Renderer() {}
	Renderer(uint32_t maxZ);

	static void constructDebugLayer(const std::string& fileNameFontTxt, const std::string& fileNameFontPng);

	static void attachLayer();

	static void setEnableLayer(uint32_t layer, bool enable = true);

	static void clearLayer();

	static uint32_t getMaxLayer() { return maxLayer; }
	static nc::SceneNode* getLayer(uint32_t layer) { return Layer[layer]; }

	static uint32_t getLayerFromH(uint32_t h) { return h * 2; }
	static uint32_t getDinamicLayerFromH(uint32_t h) { return h * 2 + 1; }

	static DebugLayer debugLayer;

	static void clearScreen(const nc::Color& color);

private:
	static uint32_t maxLayer;

	static std::vector<nc::SceneNode*> Layer;
};


