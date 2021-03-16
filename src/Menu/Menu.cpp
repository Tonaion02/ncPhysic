#include "Menu.h"





//Class Button

//Button Constructor

Button::Button(uint32_t id,	const nc::Vector2i& min, const nc::Vector2i& max, TypeButton typeButton, const std::string& fileName)
	:m_id(id), m_min(min), m_max(max), m_typeButton(typeButton)
{
	//TextureLoader::loadTexture(fileName);
	m_image = Image(TextureLoader::getTexture(fileName), Renderer::getLayer(1));
}

//Button::Button(const nc::Vector2i& min, const nc::Vector2i& max, TypeButton typeButton, const Image& image)
//	:m_min(min), m_max(max), m_typeButton(typeButton), m_image(image)
//{
//
//}

//Button Constructor

bool Button::isInAreaButton(const nc::Vector2i& pos)
{
	return ((pos.x >= m_min.x && pos.x <= m_max.x) && (pos.y >= m_min.y && pos.y <= m_max.y));
}

//Move Button

void Button::moveX(int x)
{
	m_min.x += x;
	m_max.x += x;
}

void Button::moveY(int y)
{
	m_min.y += y;
	m_max.y += y;
}

//Move Button


//Class Button





//Class Page

//Page Constructor

Page::Page(const std::vector<Button>& buttons, const nc::Color& colorBackground, const std::vector<std::string>& fileNameBackgrounds, const std::vector<nc::Vector2i>& posBackgrounds)
	: m_buttons(buttons), m_colorBackground(colorBackground), m_posBackgrounds(posBackgrounds)
{
	for (int i = 0; i < fileNameBackgrounds.size(); i++)
	{
		TextureLoader::loadTexture(fileNameBackgrounds[i]);
		m_backgrounds.push_back(Image(TextureLoader::getTexture(fileNameBackgrounds[i]), Renderer::getLayer(0)));
	}
}

//Page Constructor

bool Page::isButtonPressed()
{
	for (int i = 0; i < m_buttons.size(); i++)
	{
		if (m_buttons[i].isInAreaButton(Input::getMousePos()))
		{
			m_lastButtonPressed = i;
			return true;
		}
	}

	m_lastButtonPressed = -1;
	return false;
}

Button& Page::getLastButtonPressed()
{
	//getLastButtonPressed va chiamato solo quando
	assert(m_lastButtonPressed >= 0);

	return m_buttons[m_lastButtonPressed];
}

void Page::draw()
{
	nc::theApplication().gfxDevice().setClearColor((nc::Colorf)m_colorBackground);

	for (int i = 0; i < m_backgrounds.size(); i++)
	{
		m_backgrounds[i].draw(m_posBackgrounds[i], 0);
	}

	for (int i = 0; i < m_buttons.size(); i++)
	{
		m_buttons[i].getImage().draw(m_buttons[i].getPosX(), nc::theApplication().height() - m_buttons[i].getPosY(), 1);
	}
}

//Class Page





//Class Menu

Menu::Menu(const std::string& fileName) 
	: m_previousPage(0), m_currentPage(0)
{
	std::vector<std::string> lines = getlines(fileName);
	std::vector<std::string> imageButtonFileName;
	
	std::string& line = lines[0];
	for (int i = 0; i < lines.size(); i++)
	{
		line = lines[i];
		if (!isCommentLine(line))
		{
			if (findInString(line, "imageButton="))
			{
				line = stride(line, "(");
				line = remove(line, ")");
				int a = 0;
				TextureLoader::loadTexture("../triEngine-data/data/images/" + line);
				imageButtonFileName.push_back("../triEngine-data/data/images/" + line);
			}
			else if (findInString(line, "page"))
			{
				std::vector<Button> buttons;
				nc::Color color;

				i++;
				while (!findInString(line, "]"))
				{
					line = lines[i];
					if (findInString(line, "button="))
					{
						line = stride(line, "(");
						line = remove(line, ")");
						std::vector<std::string> str = split(line, ",");
						
						buttons.push_back(Button(std::stoi(str[0]), { std::stoi(str[3]), std::stoi(str[4]) }, {std::stoi(str[5]), std::stoi(str[6])}, (TypeButton)std::stoi(str[2]), imageButtonFileName[std::stoi(str[1])]));
					}
					else if (findInString(line, "color="))
					{
						line = stride(line, "(");
						line = remove(line, ")");
						std::vector<std::string> str = split(line, ",");

						color = nc::Color(std::stoi(str[0]), std::stoi(str[1]), std::stoi(str[2]), std::stoi(str[3]));
					}

					i++;
				}

				m_pages.push_back(Page(buttons, color, {}, {}));
			}
		}
	}
}

void Menu::nextPage(int32_t nextPage)
{
	assert(nextPage >= 0 && nextPage < m_pages.size());

	m_previousPage = m_currentPage;
	m_currentPage = nextPage;
}

void Menu::previousPage()
{
	std::swap(m_currentPage, m_previousPage);
}

uint32_t Menu::getIndexCurrentPage()
{
	return m_currentPage;
}

//Class Menu