#pragma once

#include "PrecompiledHeaders.h"

#include "Image.h"
#include "Physic/PhysicEngine.h"

#include "Renderer/Renderer.h"





enum TypeGameObject
{
	NoneTypeGameObject = -1,
	Particle = 0,
	Wall = 1,
	rectangleEntity = 2
};





class GameObject
{
public:
	GameObject() {}
	GameObject(const std::string& fileName, const nc::Vector2i& min, const nc::Vector2i& dimension, float mass, float life, TypeGameObject typeGameObject);

	virtual void move(float elapsedTime) = 0;
	virtual void draw() = 0;
	virtual void detectColission(const GameObject& other) = 0;

	TypeGameObject getTypeGameObject() { return m_typeGameObject; }

	AABBbox m_box;

	Image m_image;
	float m_maxLife, m_currentLife;
private:

	TypeGameObject m_typeGameObject;
};





class RectangleParticle : public GameObject
{
public:
	RectangleParticle() {}
	RectangleParticle(const std::string& fileName, const nc::Vector2i& min, const nc::Vector2i& dimension, float mass, float life, float damage);

	virtual void move(float elapsedTime) override;
	virtual void draw() override;
	virtual void detectColission(const GameObject& other) override;

	bool isInLife() { return m_currentLife > 0; }

	void onMove();
	void onCreate(float elapsedTime, const nc::Vector2f& force);

	float getDamage() { return m_damage; }
private:
	float m_damage;
};





class RectangleEntity : public GameObject
{
public:
	RectangleEntity() {}
	RectangleEntity(const std::string& fileName, const nc::Vector2i& min, const nc::Vector2i& dimension, float mass, float life);
	
	virtual void move(float elapsedTime) override;
	virtual void draw() override;
	virtual void detectColission(const GameObject& other) override;

	bool isInLife() { return m_currentLife > 0; }
};





class BattleHandler
{
public:
	static BattleHandler& getInstance()
	{
		static BattleHandler instance;
		return instance;
	}

	//Create Element
	uint32_t createParticle(const std::string& fileName, const nc::Vector2i& min, const nc::Vector2i& dimension, float mass, float life, float damage);
	void createEntity(const std::string& fileName, const nc::Vector2i& min, const nc::Vector2i& dimension, float mass, float life);

	//Move Element
	void moveParticle(float elapsedTime);
	
	void detectCollisionParticle();
	void detectCollisionEntity();

	//Destroy Element
	void destroyParticle(int index);
	void destroyEntity(int index);

	void applyForce(float elapsedTime, const nc::Vector2f& force, int index);

	void draw();

	void destroyDeadElement();
private:
	BattleHandler() {}

	//Qui vector di tutti quanti gli elementi che devono interagire tra loro nel gioco
	std::vector<RectangleParticle*> s_rectangleParticles;
	std::vector<RectangleEntity*> s_rectangleEntities;
};











//class RectangleParticle
//{
//public:
//	RectangleParticle() {}
//	RectangleParticle(const std::string& fileName, const nc::Vector2i& min, const nc::Vector2i& dimension, float mass, float life);
//	
//	void detectCollision(float elapsedTime);
//	void destroyParticle();
//	void draw();
//
//public:
//	AABBbox* m_box;
//
//private:
//	Image m_image;
//	float m_maxLife, m_currentLife;
//};