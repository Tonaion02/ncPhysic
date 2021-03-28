#pragma once
//Cancellare TypeGameObject

#include "PrecompiledHeaders.h"

#include "Image.h"
#include "Physic/PhysicEngine.h"

#include "Renderer/Renderer.h"





enum TypeGameObject
{
	NoneTypeGameObject = -1,
	rectangleParticle = 0,
	rectangleWall = 1,
	rectangleEntity = 2,
	rectangleHitbox = 3
};





class GameObject
{
public:
	GameObject() {}
	GameObject(const std::string& fileName, const nc::Vector2i& min, const nc::Vector2i& dimension, float mass, float life, TypeGameObject typeGameObject);

	virtual void move(float elapsedTime) = 0;
	virtual void draw() = 0;

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

	bool isInLife() { return m_currentLife > 0; }

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

	bool isInLife() { return m_currentLife > 0; }
};





class StaticRectangleWall : public GameObject
{
public:
	StaticRectangleWall() {}
	StaticRectangleWall(const std::string& fileName, const nc::Vector2i& min, const nc::Vector2i& dimension, float mass, float life);

	virtual void move(float elapsedTime) override;
	virtual void draw() override;
};





class RectangleHitbox : public GameObject
{
public:
	RectangleHitbox() {}
	RectangleHitbox(const std::string& fileName, const nc::Vector2i& min, const nc::Vector2i& dimension, float life, float damage);

	virtual void move(float elapsedTime) override;
	virtual void draw() override;

	void updatePosition(const nc::Vector2i& min);
	void updateLife();
	bool isInLife() { return m_currentLife > 0; }

	float getDamage() { return m_damage; }

private:
	float m_damage;
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
	void createPlayerParticle(const std::string& filename, const nc::Vector2i& min, const nc::Vector2i& dimension, float mass, float life, float damage);
	
	void createEntity(const std::string& fileName, const nc::Vector2i& min, const nc::Vector2i& dimension, float mass, float life);
	void createPlayerEntity(const std::string& fileName, const nc::Vector2i& min, const nc::Vector2i& dimension, float mass, float life);

	void createStaticRectangleWalls(const std::string& fileName, const nc::Vector2i& min, const nc::Vector2i& dimension, float mass, float life);

	uint32_t createRectangleHitbox(const std::string& fileName, const nc::Vector2i& min, const nc::Vector2i& dimension, float life, float damage);
	uint32_t createPlayerRectangleHitbox(const std::string& fileName, const nc::Vector2i& min, const nc::Vector2i& dimension, float life, float damage);

	void createLimitLine(float limit, Axis axis);

	//Move Element
	void moveParticle(float elapsedTime);
	void movePlayerEntities(float elapsedTime);

	//Update Position Hitbox
	void updatePositionRectangleHitbox(const nc::Vector2i& min, int index);
	void updatePositionPlayerRectangleHitbox(const nc::Vector2i& min, int index);

	//Update Life RectangleHitbox
	void updateLifeRectangleHitbox();
	void updateLifePlayerRectangleHitbox();
	
	//Detect Collision
	void detectCollisionParticle();
	void detectCollisionEntity();

	//Destroy Element
	void destroyParticle(int index);
	void destroyEntity(int index);
	void destroyPlayerEntity(int index);
	void destroyPlayerParticle(int index);
	void destroyHitbox(int index);
	void destroyPlayerHitbox(int index);

	//Apply Force
	void applyForceOnParticle(float elapsedTime, const nc::Vector2f& force, int index);
	void applyForceOnPlayerEntities(float elapsedTime, const nc::Vector2f& force, int index);

	//Apply Friction
	void applyFrictionOnPlayerEntities(float elapsedTime);

	//Get One Element
	RectangleEntity* getPlayerRectangleEntities(int index) { return s_playerRectangleEntities[index]; }

	void draw();

	void destroyDeadElement();
private:
	BattleHandler() {}

	//Qui vector di tutti quanti gli elementi che devono interagire tra loro nel gioco
	std::vector<RectangleParticle*> s_rectangleParticles;
	std::vector<RectangleEntity*> s_rectangleEntities;

	std::vector<RectangleParticle*> s_playerRectangleParticles;
	std::vector<RectangleEntity*> s_playerRectangleEntities;

	std::vector<StaticRectangleWall*> s_rectangleWalls;

	std::vector<RectangleHitbox*> s_rectangleHitbox;
	std::vector<RectangleHitbox*> s_playerRectangleHitbox;
 
	std::vector<Line> s_limitLines;
};