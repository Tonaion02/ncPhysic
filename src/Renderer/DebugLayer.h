#pragma once

#include "PrecompiledHeaders.h"

#include "nctl/UniquePtr.h"

#include "ncine/Application.h"
#include "ncine/TextNode.h"
#include "ncine/Font.h"





namespace nc = ncine;

class DebugLayer
{
public:
	DebugLayer() {}
	DebugLayer(const std::string& fileNameFontTxt, const std::string& fileNameFontPng, const nc::Color& standardColor = {0, 0, 0, 255});

	void addDebugString(const std::string& debugString);
	void addDebugString(const std::string& debugString, int index);

	void setDebugString(const std::string& debugString, int index);
	
	void setDrawEnableTrue();
	void setDrawEnableFalse();

	void setDrawEnable(int index, bool drawEnabled);

	void deleteDebugString(int index);

private:
	//Forse aggiungere
	void recalculatePos();

private:
	nctl::UniquePtr<nc::Font> m_font;
	std::vector<nctl::UniquePtr<nc::TextNode>> m_textNodes;
	nc::Color m_standardColor;

	//std::vector<nctl::String> m_debugStrings;
};