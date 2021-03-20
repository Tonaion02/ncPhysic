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
	:GameObject(fileName, min, dimension, mass, life, TypeGameObject::Particle), m_damage(damage)
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

void RectangleParticle::detectColission(const GameObject& other)
{

}

void RectangleParticle::onMove()
{
	
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

}

void RectangleEntity::draw()
{
	m_image.draw(m_box.getIntCenter().x, m_box.getIntCenter().y, Renderer::getLayerFromH(1));
}

void RectangleEntity::detectColission(const GameObject& other)
{

}

//RectangleEntity Class





//GameHandler Class

//Create Element
uint32_t BattleHandler::createParticle(const std::string& fileName, const nc::Vector2i& min, const nc::Vector2i& dimension, float mass, float life, float damage)
{
	s_rectangleParticles.push_back(new RectangleParticle(fileName, min, dimension, mass, life, damage));
	return s_rectangleParticles.size() - 1;
}

void BattleHandler::createEntity(const std::string& fileName, const nc::Vector2i& min, const nc::Vector2i& dimension, float mass, float life)
{
	s_rectangleEntities.push_back(new RectangleEntity(fileName, min, dimension, mass, life));
}
//Create Element

//Move Element
void BattleHandler::moveParticle(float elapsedTime)
{
	for (int i = 0; i < s_rectangleParticles.size(); i++)
	{
		s_rectangleParticles[i]->move(elapsedTime);
	}
}
//Move Element

//Detect Collision Element
void BattleHandler::detectCollisionParticle()
{
	for (int i = 0; i < s_rectangleParticles.size(); i++)
	{
		for (int j = 0; j < s_rectangleEntities.size(); j++)
		{
			if (s_rectangleParticles[i]->m_box.detection(s_rectangleEntities[j]->m_box))
			{
				s_rectangleParticles[i]->m_currentLife = 0.0f;
			}
		}
	}
}

void BattleHandler::detectCollisionEntity()
{
	for (int i = 0; i < s_rectangleEntities.size(); i++)
	{

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
//Destroy Element

void BattleHandler::applyForce(float elapsedTime, const nc::Vector2f& force, int index)
{
	s_rectangleParticles[index]->m_box.applyForce(elapsedTime, force);
}

//Draw Routine
void BattleHandler::draw()
{
	for (int i = 0; i < s_rectangleParticles.size(); i++)
	{
		s_rectangleParticles[i]->draw();
	}

	for (int i = 0; i < s_rectangleEntities.size(); i++)
	{
		s_rectangleEntities[i]->draw();
	}
}
//Draw Routine

//Clear Routine
void BattleHandler::destroyDeadElement()
{
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
}
//Clear Routine

//GameHandler Class