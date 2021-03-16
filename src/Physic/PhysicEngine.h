#pragma once

#include "ncine/Vector2.h"

#include "PrecompiledHeaders.h"

#include "Physic/PhysicEngine.h"





namespace nc = ncine;

enum TypeAABB
{
	NoneTypeAABB = -1,
	rigidBody = 0,
	rectangleHitBox = 1,
	rectangleParticle = 2
};

class AABBbox
{
public:
	AABBbox() {}
	AABBbox(const nc::Vector2f& min, const nc::Vector2i& dimension, float mass, TypeAABB type);
	~AABBbox() {}

	//void moveX(float spaceX) { m_min.x += spaceX; m_max.x += spaceX; }
	//void moveY(float spaceY) { m_min.y += spaceY; m_max.y += spaceY; }
	//void move(const nc::Vector2f& space) { m_min.x += space.x; m_max.x += space.x; m_min.y += space.y; m_max.y += space.y; }

	void moveX(float elapsedTime);
	void moveY(float elapsedTime);
	void move(const nc::Vector2f& space) { m_min.x += space.x; m_max.x += space.x; m_min.y += space.y; m_max.y += space.y; }

	//Aggiungere ApplyForce
	void applyForce(float elapsedTime, const nc::Vector2f& force) 
	{ 
		nc::Vector2f a = { force.x / m_mass, force.y / m_mass }; 
		m_v = { m_v.x + a.x * elapsedTime, m_v.y + a.y * elapsedTime }; 
	}

	nc::Vector2f getCenter() { return { (m_min.x + m_max.x) / 2.0f, (m_min.y + m_max.y) / 2 }; }
	nc::Vector2i getIntCenter() { return { int32_t((m_min.x + m_max.x) / 2), int32_t((m_min.y + m_max.y) / 2) }; }

	nc::Vector2f getV() { return m_v; }
	void setV(const nc::Vector2f& v) { m_v = v; }

	float getMass() { return m_mass; }

	TypeAABB getTypeAABB() { return typeAABB; }

	bool detectionX(AABBbox* box);
	bool detectionY(AABBbox* box);
	bool detection(AABBbox* box);

public:
	nc::Vector2f m_min, m_max;

private:
	//Non utilizzati
	float m_mass;
	nc::Vector2f m_v;

	TypeAABB typeAABB;
};




class PhysicEngine
{
public:
	static PhysicEngine& getInstance()
	{
		static PhysicEngine instance;
		return instance;
	}
	
	void update(float elapsedTime);
	void addAABBbox(AABBbox* box);

	float conversionFromMeterToPixel(float space);
private:
	PhysicEngine() {}

	float calculateDistanceX(const AABBbox& box, const AABBbox& box2);
	float calculateDistanceY(const AABBbox& box, const AABBbox& box2);
	
	void collisionResponseX(AABBbox* box, AABBbox* box2);
	void collisionResponseY(AABBbox* box, AABBbox* box2);
	
private:
	std::vector<AABBbox*> boxes;
};



