#pragma once

#include "PrecompiledHeaders.h"

#include "Renderer/Renderer.h"

#include "Input/Input.h"

#include "AddonsString.h"

#include "Image.h"





enum TypeButton
{
	NullTypeButton = -1,
	Normal = 0,
	ChangePage = 1,
	LoadAnotherPage = 2,
	MoveableButton = 3
};





class Button
{
public:
	Button() {}
	Button(uint32_t id, const nc::Vector2i& min, const nc::Vector2i& max, TypeButton typeButton, const std::string& fileName);
	//Button(const nc::Vector2i& min, const nc::Vector2i& max, TypeButton typeButton, const Image& image);

	bool isInAreaButton(const nc::Vector2i& pos);
	
	uint32_t getIdButton() { return m_id; }

	Image& getImage() { return m_image; }

	TypeButton getTypeButton() { return m_typeButton; }

	int32_t getPosX() { return m_min.x + ((m_max.x - m_min.x) / 2); }
	int32_t getPosY() { return m_min.y + ((m_max.y - m_min.y) / 2); }

	void moveX(int x);
	void moveY(int y);

	//Non so se usarlo
	virtual void onButtonPressed() {};

protected: 
	nc::Vector2i m_min, m_max;
	TypeButton m_typeButton;
	uint32_t m_id;

	Image m_image;
};





//class NormalButton : public Button
//{
//public:
//	friend Button;
//
//public:
//	NormalButton() {}
//	NormalButton(const nc::Vector2i& min, const nc::Vector2i& max, TypeButton typeButton, const std::string& fileName);
//
//private:
//
//};





class Page
{
public:
	Page() {}
	Page(const std::vector<Button>& buttons, const nc::Color& colorBackground, const std::vector<std::string>& fileNameBackgrounds, const std::vector<nc::Vector2i>& posBackgrounds);
	
	bool isButtonPressed();
	Button& getLastButtonPressed();

	void draw();

private:
	std::vector<Button> m_buttons;

	//Forse
	//Non so se voglio gestirli così
	std::vector<Image> m_backgrounds;
	std::vector<nc::Vector2i> m_posBackgrounds;

	nc::Color m_colorBackground;

	int32_t m_lastButtonPressed;
};





class Menu
{
public:
	Menu() {}
	Menu(const std::string& fileName);

	void nextPage(int32_t nextPage);
	void previousPage();

	uint32_t getIndexCurrentPage();

	std::vector<Page> m_pages;

private:
	uint32_t m_currentPage;
	uint32_t m_previousPage;
};