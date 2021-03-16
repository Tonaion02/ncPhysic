#include "DebugLayer.h"





//DebugLayer Class

//DebugLayer Constructor

DebugLayer::DebugLayer(const std::string& fileNameFontTxt, const std::string& fileNameFontPng, const nc::Color& standardColor)
{
	m_font = nctl::makeUnique<nc::Font>(fileNameFontTxt.c_str(), fileNameFontPng.c_str());
	m_standardColor = standardColor;
}

//DebugLayer Constructor

//Set DebugLayer String

void DebugLayer::recalculatePos()
{
	for (int i = 0; i < m_textNodes.size(); i++)
	{
		m_textNodes[i]->setPosition(nc::theApplication().width() - (m_textNodes[i]->width() / 2), nc::theApplication().height() - (m_textNodes[i]->height() / 2) - (m_textNodes[i]->height() * (i)));
	}
}

void DebugLayer::addDebugString(const std::string& debugString)
{
	nctl::String dString = nctl::String(debugString.size() + 1);
	dString = debugString.c_str();
	m_textNodes.push_back(nctl::makeUnique<nc::TextNode>(&nc::theApplication().rootNode(), m_font.get()));

	m_textNodes[m_textNodes.size() - 1]->setString(dString);
	m_textNodes[m_textNodes.size() - 1]->setPosition(nc::theApplication().width() - (m_textNodes[m_textNodes.size() - 1]->width() / 2),
		nc::theApplication().height() - (m_textNodes[m_textNodes.size() - 1]->height() / 2) - ((m_textNodes.size()-1) * m_textNodes[m_textNodes.size()-1]->height()));
	m_textNodes[m_textNodes.size() - 1]->setColor(m_standardColor);
}

void DebugLayer::addDebugString(const std::string& debugString, int index)
{
	assert(index >= 0 && index < m_textNodes.size());

	nctl::String dString = nctl::String(debugString.size() + 1);
	dString = debugString.c_str();

	m_textNodes.emplace(m_textNodes.begin() + index, nctl::makeUnique<nc::TextNode>(&nc::theApplication().rootNode(), m_font.get()));
	m_textNodes[index]->setString(dString);
	m_textNodes[index]->setColor(m_standardColor);

	this->recalculatePos();

}

void DebugLayer::setDebugString(const std::string& debugString, int index)
{
	assert(index >= 0 && index < m_textNodes.size());

	nctl::String dString = nctl::String(debugString.size() + 1);
	dString = debugString.c_str();
	m_textNodes[index]->setString(dString);
	m_textNodes[index]->setPosition(nc::theApplication().width() - (m_textNodes[index]->width() / 2), nc::theApplication().height() - (m_textNodes[index]->height()));

	this->recalculatePos();
}

//Set DebugLayer String

//Delete DebugLayer String

void DebugLayer::deleteDebugString(int index)
{
	assert(index >= 0 && index < m_textNodes.size());

	m_textNodes[index]->setDrawEnabled(false);
	m_textNodes[index].release();
	m_textNodes.erase(m_textNodes.begin()+index);

	this->recalculatePos();
	
}

//Delete DebugLayer String

//Set Draw Enabled

void DebugLayer::setDrawEnableTrue()
{
	for (int i = 0; i < m_textNodes.size(); i++)
	{
		m_textNodes[i]->setDrawEnabled(true);
	}
}

void DebugLayer::setDrawEnableFalse()
{
	for (int i = 0; i < m_textNodes.size(); i++)
	{
		m_textNodes[i]->setDrawEnabled(false);
	}
}

void DebugLayer::setDrawEnable(int index, bool drawEnabled)
{
	m_textNodes[index]->setDrawEnabled(drawEnabled);
}

//Set Draw Enabled

//DebugLayer Class