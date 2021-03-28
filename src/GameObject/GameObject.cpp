#include "GameObject.h"





//GameObject class

//GameObject Constructor

GameObject::GameObject(const std::string& fileName, const nc::Vector2i& min, const nc::Vector2i& dimension, float mass, float life, TypeGameObject typeGameObject)
	:m_box(AABBbox(min, dimension, mass)), m_maxLife(life), m_currentLife(life), m_typeGameObject(typeGameObject)
{
	TextureLoader::loadTexture(fileName);
	m_image = Image(TextureLoader::getTexture(fileName), Renderer::getLayer(0));
}

//GameObject Constructor

//GameObject class





//RectangleParticle class

//RectangleParticle constructor

RectangleParticle::RectangleParticle(const std::string& fileName, const nc::Vector2i& min, const nc::Vector2i& dimension, float mass, float life,float damage)
	:GameObject(fileName, min, dimension, mass, life, TypeGameObject::rectangleParticle), m_damage(damage)
{
	
}

//RectangleParticle constructor

//Override RectangleParticle

void RectangleParticle::move(float elapsedTime) 
{
	m_currentLife -= 0.01f;
	m_box.moveX(elapsedTime);
	m_box.moveY(elapsedTime);
}

void RectangleParticle::draw()
{
	float opacity = m_currentLife / m_maxLife;
	if (opacity < 0.1f)
	{
		opacity = 0.1f;
	}
	m_image.setAlpha(opacity);
	m_image.draw(m_box.getIntCenter().x, m_box.getIntCenter().y, Renderer::getLayerFromH(1));
}

void RectangleParticle::onCreate(float elapsedTime, const nc::Vector2f& force)
{
	m_box.applyForce(elapsedTime, force);
}

//Override RectangleParticle

//RectangleParticle class





//RectangleEntity Class

RectangleEntity::RectangleEntity(const std::string& fileName, const nc::Vector2i& min, const nc::Vector2i& dimension, float mass, float life)
	:GameObject(fileName, min, dimension, mass, life, TypeGameObject::rectangleEntity)
{

}

void RectangleEntity::move(float elapsedTime)
{
	m_box.moveX(elapsedTime);
	m_box.moveY(elapsedTime);
}

void RectangleEntity::draw()
{
	m_image.draw(m_box.getIntCenter().x, m_box.getIntCenter().y, Renderer::getLayerFromH(1));
}

//RectangleEntity Class





//StaticRectangleWall Class
StaticRectangleWall::StaticRectangleWall(const std::string& fileName, const nc::Vector2i& min, const nc::Vector2i& dimension, float mass, float life)
	:GameObject(fileName, min, dimension, mass, life, TypeGameObject::rectangleWall)
{

}

void StaticRectangleWall::draw()
{
	m_image.draw(m_box.getIntCenter().x, m_box.getIntCenter().y, Renderer::getLayerFromH(1));
}

void StaticRectangleWall::move(float elapsedTime)
{

}
//StaticRectangleWall Class





//RectangleHitbox Class
RectangleHitbox::RectangleHitbox(const std::string& fileName, const nc::Vector2i& min, const nc::Vector2i& dimension, float life, float damage)
	:GameObject(fileName, min, dimension, 0, life, TypeGameObject::rectangleHitbox), m_damage(damage)
{

}

void RectangleHitbox::move(float elapsedTime)
{

}

void RectangleHitbox::draw()
{
	m_image.draw(m_box.getIntCenter().x, m_box.getIntCenter().y, Renderer::getLayerFromH(1));
}

void RectangleHitbox::updatePosition(const nc::Vector2i& min)
{
	m_box.m_max = { min.x + (m_box.m_max.x - m_box.m_min.x), min.y + (m_box.m_max.y - m_box.m_min.y) };
	m_box.m_min = { (float)min.x, (float)min.y };
}

void RectangleHitbox::updateLife()
{
	m_currentLife -= 0.01f;
}
//RectangleHitbox Class





//GameHandler Class

//Create Element
uint32_t BattleHandler::createParticle(const std::string& fileName, const nc::Vector2i& min, const nc::Vector2i& dimension, float mass, float life, float damage)
{
	s_rectangleParticles.push_back(new RectangleParticle(fileName, min, dimension, mass, life, damage));
	return s_rectangleParticles.size() - 1;
}

void BattleHandler::createPlayerParticle(const std::string& fileName, const nc::Vector2i& min, const nc::Vector2i& dimension, float mass, float life, float damage)
{
	s_playerRectangleParticles.push_back(new RectangleParticle(fileName, min, dimension, mass, life, damage));
}

void BattleHandler::createEntity(const std::string& fileName, const nc::Vector2i& min, const nc::Vector2i& dimension, float mass, float life)
{
	s_rectangleEntities.push_back(new RectangleEntity(fileName, min, dimension, mass, life));
}

void BattleHandler::createPlayerEntity(const std::string& fileName, const nc::Vector2i& min, const nc::Vector2i& dimension, float mass, float life)
{
	s_playerRectangleEntities.push_back(new RectangleEntity(fileName, min, dimension, mass, life));
}

void BattleHandler::createStaticRectangleWalls(const std::string& fileName, const nc::Vector2i& min, const nc::Vector2i& dimension, float mass, float life)
{
	s_rectangleWalls.push_back(new StaticRectangleWall(fileName, min, dimension, mass, life));
}

uint32_t BattleHandler::createRectangleHitbox(const std::string& fileName, const nc::Vector2i& min, const nc::Vector2i& dimension, float life, float damage)
{
	s_rectangleHitbox.push_back(new RectangleHitbox(fileName, min, dimension, life, damage));
	return s_rectangleHitbox.size() - 1;
}

uint32_t BattleHandler::createPlayerRectangleHitbox(const std::string& fileName, const nc::Vector2i& min, const nc::Vector2i& dimension, float life, float damage)
{
	s_playerRectangleHitbox.push_back(new RectangleHitbox(fileName, min, dimension, life, damage));
	return s_playerRectangleHitbox.size() - 1;
}

void BattleHandler::createLimitLine(float limit, Axis axis)
{
	s_limitLines.push_back(Line(limit, axis));
}
//Create Element





//Move Element
void BattleHandler::movePlayerEntities(float elapsedTime)
{
	for (int i = 0; i < s_playerRectangleEntities.size(); i++)
	{
		RectangleEntity copy = *s_playerRectangleEntities[i];
		s_playerRectangleEntities[i]->m_box.moveX(elapsedTime);

		for (int j = 0; j < s_rectangleWalls.size(); j++)
		{
			if (s_playerRectangleEntities[i]->m_box.detection(s_rectangleWalls[j]->m_box))
			{
				*s_playerRectangleEntities[i] = copy;
				float spaceX = PhysicEngine::getInstance().calculateDistanceX(s_playerRectangleEntities[i]->m_box, s_rectangleWalls[j]->m_box);
				if (s_playerRectangleEntities[i]->m_box.getV().x < 0.0f)
				{
					spaceX = -std::abs(spaceX);
				}
				s_playerRectangleEntities[i]->m_box.move({ spaceX, 0.0f });
			}
		}

		for (int j = 0; j < s_limitLines.size(); j++)
		{
			if (s_limitLines[j].inLine(s_playerRectangleEntities[i]->m_box))
			{
				*s_playerRectangleEntities[i] = copy;
				float spaceX = PhysicEngine::getInstance().calculateDistance(s_playerRectangleEntities[i]->m_box, s_limitLines[j]);
				if (s_playerRectangleEntities[i]->m_box.getV().x < 0.0f)
				{
					spaceX = -std::abs(spaceX);
				}
				s_playerRectangleEntities[i]->m_box.move({ spaceX, 0.0f });
			}
		}

		copy = *s_playerRectangleEntities[i];
		s_playerRectangleEntities[i]->m_box.moveY(elapsedTime);

		for (int j = 0; j < s_rectangleWalls.size(); j++)
		{
			if (s_playerRectangleEntities[i]->m_box.detection(s_rectangleWalls[j]->m_box))
			{
				*s_playerRectangleEntities[i] = copy;
				float spaceY = PhysicEngine::getInstance().calculateDistanceY(s_playerRectangleEntities[i]->m_box, s_rectangleWalls[j]->m_box);
				if (s_playerRectangleEntities[i]->m_box.getV().y < 0.0f)
				{
					spaceY = -std::abs(spaceY);
				}
				s_playerRectangleEntities[i]->m_box.move({ 0.0f, spaceY });
			}
		}

		for (int j = 0; j < s_limitLines.size(); j++)
		{
			if (s_limitLines[j].inLine(s_playerRectangleEntities[i]->m_box))
			{
				*s_playerRectangleEntities[i] = copy;
				float spaceY = PhysicEngine::getInstance().calculateDistance(s_playerRectangleEntities[i]->m_box, s_limitLines[j]);
				if (s_playerRectangleEntities[i]->m_box.getV().y < 0.0f)
				{
					spaceY = -std::abs(spaceY);
				}
				s_playerRectangleEntities[i]->m_box.move({ 0.0f, spaceY });
			}
		}
	}
}

void BattleHandler::moveParticle(float elapsedTime)
{
	for (int i = 0; i < s_rectangleParticles.size(); i++)
	{
		s_rectangleParticles[i]->move(elapsedTime);
	}
}
//Move Element





//Update Position Element
void BattleHandler::updatePositionRectangleHitbox(const nc::Vector2i& min, int index)
{
	s_rectangleHitbox[index]->m_box.m_max = { min.x + (s_rectangleHitbox[index]->m_box.m_max.x - s_rectangleHitbox[index]->m_box.m_min.x), min.y + (s_rectangleHitbox[index]->m_box.m_max.y - s_rectangleHitbox[index]->m_box.m_min.y) };
	s_rectangleHitbox[index]->m_box.m_min = { (float)min.x, (float)min.y };
}
void BattleHandler::updatePositionPlayerRectangleHitbox(const nc::Vector2i& min, int index)
{
	s_playerRectangleHitbox[index]->m_box.m_max = { min.x + (s_playerRectangleHitbox[index]->m_box.m_max.x - s_playerRectangleHitbox[index]->m_box.m_min.x), min.y + (s_playerRectangleHitbox[index]->m_box.m_max.y - s_playerRectangleHitbox[index]->m_box.m_min.y) };
	s_playerRectangleHitbox[index]->m_box.m_min = { (float)min.x, (float)min.y };
}
//Update Position Element





//Update Life Element
void BattleHandler::updateLifeRectangleHitbox()
{
	for (int i = 0; i < s_rectangleHitbox.size(); i++)
	{
		s_rectangleHitbox[i]->m_currentLife -= 0.01f;
	}
}

void BattleHandler::updateLifePlayerRectangleHitbox()
{
	for (int i = 0; i < s_playerRectangleHitbox.size(); i++)
	{
		s_playerRectangleHitbox[i]->m_currentLife -= 0.01f;
	}
}
//Update Life Element





//Detect Collision Element
void BattleHandler::detectCollisionParticle()
{
	for (int i = 0; i < s_rectangleParticles.size(); i++)
	{
		for (int j = 0; j < s_playerRectangleEntities.size(); j++)
		{
			if (s_rectangleParticles[i]->m_box.detection(s_playerRectangleEntities[j]->m_box))
			{
				s_rectangleParticles[i]->m_currentLife = 0.0f;
				break;
			}
		}

		for (int j = 0; j < s_rectangleWalls.size(); j++)
		{
			if (s_rectangleParticles[i]->m_box.detection(s_rectangleWalls[j]->m_box))
			{
				s_rectangleParticles[i]->m_currentLife = 0.0f;
				break;
			}
		}
	}

	for (int i = 0; i < s_playerRectangleParticles.size(); i++)
	{
		for (int j = 0; j < s_rectangleEntities.size(); j++)
		{
			if (s_playerRectangleParticles[i]->m_box.detection(s_rectangleEntities[j]->m_box))
			{
				s_playerRectangleParticles[i]->m_currentLife = 0.0f;
				break;
			}
		}

		for (int j = 0; j < s_rectangleWalls.size(); j++)
		{
			if (s_playerRectangleParticles[i]->m_box.detection(s_rectangleWalls[j]->m_box))
			{
				s_playerRectangleParticles[i]->m_currentLife = 0.0f;
				break;
			}
		}
	}
}

void BattleHandler::detectCollisionEntity()
{
	//Player Entities
	for (int i = 0; i < s_playerRectangleEntities.size(); i++)
	{
		for (int j = 0; j < s_rectangleParticles.size(); j++)
		{
			if (s_playerRectangleEntities[i]->m_box.detection(s_rectangleParticles[j]->m_box) && s_rectangleParticles[j]->isInLife())
			{
				s_playerRectangleEntities[i]->m_currentLife -= s_rectangleParticles[j]->getDamage();
			}
		}

		for (int j = 0; j < s_rectangleHitbox.size(); j++)
		{
			if (s_playerRectangleEntities[i]->m_box.detection(s_rectangleHitbox[j]->m_box) && s_rectangleHitbox[j]->isInLife())
			{
				s_playerRectangleEntities[i]->m_currentLife -= s_rectangleHitbox[j]->getDamage();
			}
		}
	}
	//Player Entities

	for (int i = 0; i < s_rectangleEntities.size(); i++)
	{
		for (int j = 0; j < s_playerRectangleParticles.size(); j++)
		{
			if (s_rectangleEntities[i]->m_box.detection(s_playerRectangleParticles[j]->m_box) && s_playerRectangleParticles[j]->isInLife())
			{
				s_rectangleEntities[i]->m_currentLife -= s_playerRectangleParticles[j]->getDamage();
			}
		}

		for (int j = 0; j < s_playerRectangleHitbox.size(); j++)
		{
			if (s_rectangleEntities[i]->m_box.detection(s_playerRectangleHitbox[j]->m_box) && s_playerRectangleHitbox[j]->isInLife())
			{
				s_rectangleEntities[i]->m_currentLife -= s_playerRectangleHitbox[j]->getDamage();
			}
		}
	}
}
//Detect Collision Element





//Destroy Element
void BattleHandler::destroyParticle(int index)
{
	s_rectangleParticles[index]->m_image.destroy();
	delete s_rectangleParticles[index];
	s_rectangleParticles.erase(s_rectangleParticles.begin() + index);
}

void BattleHandler::destroyEntity(int index)
{
	s_rectangleEntities[index]->m_image.destroy();
	delete s_rectangleEntities[index];
	s_rectangleEntities.erase(s_rectangleEntities.begin() + index);
}

void BattleHandler::destroyHitbox(int index)
{
	s_rectangleHitbox[index]->m_image.destroy();
	delete s_rectangleHitbox[index];
	s_rectangleHitbox.erase(s_rectangleHitbox.begin() + index);
}

void BattleHandler::destroyPlayerEntity(int index)
{
	s_playerRectangleEntities[index]->m_image.destroy();
	delete s_playerRectangleEntities[index];
	s_playerRectangleEntities.erase(s_playerRectangleEntities.begin() + index);
}

void BattleHandler::destroyPlayerParticle(int index)
{
	s_playerRectangleParticles[index]->m_image.destroy();
	delete s_playerRectangleParticles[index];
	s_playerRectangleParticles.erase(s_playerRectangleParticles.begin() + index);
}

void BattleHandler::destroyPlayerHitbox(int index)
{
	s_playerRectangleHitbox[index]->m_image.destroy();
	delete s_playerRectangleHitbox[index];
	s_playerRectangleHitbox.erase(s_playerRectangleHitbox.begin() + index);
}
//Destroy Element





//Apply Force On an Element
void BattleHandler::applyForceOnParticle(float elapsedTime, const nc::Vector2f& force, int index)
{
	s_rectangleParticles[index]->m_box.applyForce(elapsedTime, force);
}

void BattleHandler::applyForceOnPlayerEntities(float elapsedTime, const nc::Vector2f& force, int index)
{
	s_playerRectangleEntities[index]->m_box.applyForce(elapsedTime, force);
}
//Apply Force On an Element





//Friction
void BattleHandler::applyFrictionOnPlayerEntities(float elapsedTime)
{
	for (int i = 0; i < s_playerRectangleEntities.size(); i++)
	{
		int signX=1, signY=1;
		float frictionX = 0.0f, frictionY = 0.0f;
		if (std::abs(s_playerRectangleEntities[i]->m_box.getV().x) > 0)
		{
			frictionX = s_playerRectangleEntities[i]->m_box.getMass() * 9.81 * 0.5f;
			if (s_playerRectangleEntities[i]->m_box.getV().x > 0)
			{
				frictionX = -frictionX;
			}
			else if (s_playerRectangleEntities[i]->m_box.getV().x < 0)
			{
				signX = -1;
			}
		}

		if (std::abs(s_playerRectangleEntities[i]->m_box.getV().y) > 0)
		{
			frictionY = s_playerRectangleEntities[i]->m_box.getMass() * 9.81 * 0.5f;
			if (s_playerRectangleEntities[i]->m_box.getV().y > 0)
			{
				frictionY = -frictionY;
			}
			else if (s_playerRectangleEntities[i]->m_box.getV().y < 0)
			{
				signY = -1;
			}
		}

		nc::Vector2f friction = { frictionX, frictionY };
		s_playerRectangleEntities[i]->m_box.applyForce(elapsedTime, friction);
		if ((s_playerRectangleEntities[i]->m_box.getV().x > 0 && signX < 0) || (s_playerRectangleEntities[i]->m_box.getV().x < 0 && signX > 0))
		{
			s_playerRectangleEntities[i]->m_box.setV({0.0f, 0.0f});
		}
		if ((s_playerRectangleEntities[i]->m_box.getV().y > 0 && signY < 0) || (s_playerRectangleEntities[i]->m_box.getV().y < 0 && signY > 0))
		{
			s_playerRectangleEntities[i]->m_box.setV({ 0.0f, 0.0f });
		}
	}

}
//Friction





//Draw Routine
void BattleHandler::draw()
{
	for (int i = 0; i < s_playerRectangleEntities.size(); i++)
	{
		s_playerRectangleEntities[i]->draw();
	}

	for (int i = 0; i < s_playerRectangleParticles.size(); i++)
	{
		s_playerRectangleParticles[i]->draw();
	}

	for (int i = 0; i < s_playerRectangleHitbox.size(); i++)
	{
		s_playerRectangleHitbox[i]->draw();
	}

	for (int i = 0; i < s_rectangleEntities.size(); i++)
	{
		s_rectangleEntities[i]->draw();
	}

	for (int i = 0; i < s_rectangleParticles.size(); i++)
	{
		s_rectangleParticles[i]->draw();
	}

	for (int i = 0; i < s_rectangleHitbox.size(); i++)
	{
		s_rectangleHitbox[i]->draw();
	}

	for (int i = 0; i < s_rectangleWalls.size(); i++)
	{
		s_rectangleWalls[i]->draw();
	}
}
//Draw Routine





//Clear Routine
void BattleHandler::destroyDeadElement()
{
	for (int i = 0; i < s_playerRectangleEntities.size(); i++)
	{
		if (!s_playerRectangleEntities[i]->isInLife())
		{
			BattleHandler::getInstance().destroyPlayerEntity(i);
		}
	}

	for (int i = 0; i < s_playerRectangleParticles.size(); i++)
	{
		if (!s_playerRectangleParticles[i]->isInLife())
		{
			BattleHandler::getInstance().destroyPlayerParticle(i);
		}
	}

	for (int i = 0; i < s_playerRectangleHitbox.size(); i++)
	{
		if (!s_playerRectangleHitbox[i]->isInLife())
		{
			BattleHandler::getInstance().destroyPlayerHitbox(i);
		}
	}

	for (int i = 0; i < s_rectangleEntities.size(); i++)
	{
		if (!s_rectangleEntities[i]->isInLife())
		{
			BattleHandler::getInstance().destroyEntity(i);
		}
	}

	for (int i = 0; i < s_rectangleParticles.size(); i++)
	{
		if (!s_rectangleParticles[i]->isInLife())
		{
			BattleHandler::getInstance().destroyParticle(i);
		}
	}

	for (int i = 0; i < s_rectangleHitbox.size(); i++)
	{
		if (!s_rectangleHitbox[i]->isInLife())
		{
			BattleHandler::getInstance().destroyHitbox(i);
		}
	}
}
//Clear Routine

//GameHandler Class