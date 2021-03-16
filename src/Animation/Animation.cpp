#include "Animation.h"





//Class StaticAnimation

StaticAnimation::StaticAnimation(const std::vector<std::string>& fileNames, float time, const nc::Vector2i& pos, int32_t h)
	:m_pos(pos), m_h(h), m_time(time)
{
	for (int i = 0; i < fileNames.size(); i++)
	{
		TextureLoader::loadTexture(fileNames[i]);
		m_images.push_back(Image(TextureLoader::getTexture(fileNames[i]), Renderer::getLayer(1)));
	}

	m_incrementIndex = 1.0f / ((m_time / (float)fileNames.size()) * Options::getInstance().getFps());
}

void StaticAnimation::animate()
{
	if (m_running)
	{
		m_index += m_incrementIndex;
		if (m_index >= m_images.size())
		{
			m_index = 0.0f;
			if(!m_loop)
			{
				m_running = false;
			}
		}
	}
}

Image& StaticAnimation::getImage()
{
	return m_images[(int)m_index];
}

nc::Vector2i StaticAnimation::getPos()
{
	return m_pos;
}

void StaticAnimation::start()
{
	m_index = 0.0f;
	m_running = true;
}

int32_t StaticAnimation::getH()
{
	return m_h;
}

void StaticAnimation::loop()
{
	m_loop = !m_loop;
}

bool StaticAnimation::isLoop()
{
	return m_loop;
}

//Class StaticAnimation





//Class DinamicAnimation

DinamicAnimation::DinamicAnimation(const std::vector<std::string>& fileNames, float timeAnimation, const nc::Vector2i& pos, int32_t h, float timeMoving, const nc::Vector2i& spaceMove)
	:StaticAnimation(fileNames, timeAnimation, pos, h), m_timeMoving(timeMoving), m_posf({(float)pos.x, (float)pos.y}), m_spaceMove(spaceMove)
{
	//m_spaceIncrement.x = m_spaceMove.x / ((m_timeMoving / fileNames.size()) * Options::getFps());
	//m_spaceIncrement.y = m_spaceMove.y / ((m_timeMoving / fileNames.size()) * Options::getFps());

	m_spaceIncrement.x = m_spaceMove.x / (m_timeMoving * Options::getInstance().getFps());
	m_spaceIncrement.y = m_spaceMove.y / (m_timeMoving * Options::getInstance().getFps());

	m_loop = true;
}

void DinamicAnimation::animate()
{
	if (m_running)
	{
		m_index += m_incrementIndex;

		if (m_index >= m_images.size())
		{
			if (m_loop)
			{
				m_index = 0.0f;
			}
			else
			{
				m_index = m_images.size() - 1;
			}
		}

		m_posf.x += m_spaceIncrement.x;
		m_posf.y += m_spaceIncrement.y;
		m_pos.x = (int)m_posf.x;
		m_pos.y = (int)m_posf.y;

		if ((int)std::round(m_posf.x) == m_end.x && (int)std::round(m_posf.y) == m_end.y)
		{
			m_running = false;
			m_pos = m_end;
			m_index = m_images.size() - 1;
		}
	
	}
}

void DinamicAnimation::start()
{
	m_index = 0.0f;
	m_running = true;
	//m_pos.x = pos.x * Options::getTileWidht();
	//m_pos.y = pos.y * Options::getTileHeight();
	m_posf.x = m_pos.x;
	m_posf.y = m_pos.y;
	m_end.x = m_pos.x + m_spaceMove.x;
	m_end.y = m_pos.y + m_spaceMove.y;
}

void DinamicAnimation::setPos(const nc::Vector2i pos)
{
	m_pos = pos;
}

//Class DinamicAnimation