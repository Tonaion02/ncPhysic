#include "PhysicEngine.h"





//AABBbox Class

//AABBbox Constructor
AABBbox::AABBbox(const nc::Vector2i& min, const nc::Vector2i& dimension, float mass)
	: m_min({ (float)min.x, (float)min.y }), m_max({ (float)min.x + dimension.x, (float)min.y + dimension.y }), m_mass(mass)
{
	m_v = { 0.0f, 0.0f };
}
//AABBbox Constructor

//AABBbox move function
void AABBbox::moveX(float elapsedTime)
{
	float x = m_v.x * elapsedTime; 
	x = PhysicEngine::getInstance().conversionFromMeterToPixel(x); 
	m_min.x += x; 
	m_max.x += x;
}
void AABBbox::moveY(float elapsedTime)
{
	float y = m_v.y * elapsedTime; 
	y = PhysicEngine::getInstance().conversionFromMeterToPixel(y); 
	m_min.y += y; 
	m_max.y += y;
}
//AABBbox move function

//AABBbox detecting collision
bool AABBbox::detectionX(AABBbox box)
{
	if (m_min.x < box.m_max.x && m_max.x > box.m_min.x)
	{
		return true;
	}
	return false;
}
bool AABBbox::detectionY(AABBbox box)
{
	if (m_min.y < box.m_max.y && m_max.y > box.m_min.y)
	{
		return true;
	}
	return false;
}
bool AABBbox::detection(AABBbox box)
{
	return this->detectionX(box) && this->detectionY(box);
}
//AABBbox detecting collision

//AABBbox Class





//Line Class

//Line Constructor
Line::Line(float limit, Axis axis)
	:m_limit(limit), m_axis(axis)
{

}
//Line Constructor

//inLine function
bool Line::inLine(const AABBbox& box)
{
	if (m_axis == Axis::x)
	{
		return ((box.m_min.x > m_limit) && (box.m_max.x < m_limit)) || ((box.m_min.x < m_limit) && (box.m_max.x > m_limit));
	}
	else if (m_axis == Axis::y)
	{
		return ((box.m_min.y > m_limit) && (box.m_max.y < m_limit)) || ((box.m_min.y < m_limit) && (box.m_max.y > m_limit));
	}
}
//inLine function

Axis Line::getAxis() const
{ 
	return m_axis; 
}

float Line::getLimit() const
{
	return m_limit;
}
//Line Class





//PhysicEngine Class

//PhysicEngine Update
void PhysicEngine::update(float elapsedTime)
{
	for (int i = 0; i < boxes.size(); i++)
	{
		AABBbox copy = *(boxes[i]);
		boxes[i]->moveX(elapsedTime);

		//Check for collision of rigidbody
		//if (boxes[i]->getTypeAABB() == TypeAABB::rigidBody)
		//{
		//	for (int j = 0; j < boxes.size(); j++)
		//	{
		//		if (j != i && boxes[j]->getTypeAABB() == TypeAABB::rigidBody)
		//		{
		//			if (boxes[i]->detection(boxes[j]))
		//			{
		//				*boxes[i] = copy;
		//				float x = PhysicEngine::getInstance().calculateDistanceX(*boxes[i], *boxes[j]);
		//				if (boxes[i]->getV().x < 0)
		//				{
		//					x = -x;
		//				}
		//				boxes[i]->move({ x, 0.0f });
		//				PhysicEngine::getInstance().collisionResponseX(boxes[i], boxes[j]);
		//			}
		//		}
		//	}
		//}
		//
		//copy = *(boxes[i]);
		//boxes[i]->moveY(elapsedTime);

		//if (boxes[i]->getTypeAABB() == TypeAABB::rigidBody)
		//{
		//	for (int j = 0; j < boxes.size(); j++)
		//	{
		//		if (j != i && boxes[j]->getTypeAABB() == TypeAABB::rigidBody)
		//		{
		//			if (boxes[i]->detection(boxes[j]))
		//			{
		//				*boxes[i] = copy;
		//				float y = PhysicEngine::getInstance().calculateDistanceY(*boxes[i], *boxes[j]);
		//				if (boxes[i]->getV().y < 0)
		//				{
		//					y = -y;
		//				}
		//				boxes[i]->move({ 0.0f, y });
		//				PhysicEngine::getInstance().collisionResponseY(boxes[i], boxes[j]);
		//			}
		//		}
		//	}
		//}
		//Check for collision of rigidbody
	}
}
//PhysicEngine Update

//PhysicEngine Conversion
float PhysicEngine::conversionFromMeterToPixel(float space)
{
	return space / 0.0003f;
}
//PhysicEngine Conversion

//PhysicEngine calculate Distance
float PhysicEngine::calculateDistanceX(const AABBbox& box, const AABBbox& box2)
{
	float min = std::max(box.m_min.x, box2.m_min.x);
	float max = std::min(box.m_max.x, box2.m_max.x);
	return min - max;
}

float PhysicEngine::calculateDistanceY(const AABBbox& box, const AABBbox& box2)
{
	float min = std::max(box.m_min.y, box2.m_min.y);
	float max = std::min(box.m_max.y, box2.m_max.y);
	return min - max;
}

float PhysicEngine::calculateDistance(const AABBbox& box, const Line& line)
{
	float d, d2, r;
	if (line.getAxis() == Axis::x)
	{
		d = std::abs(line.getLimit() - box.m_min.x);
		d2 = std::abs(line.getLimit() - box.m_max.x);
		r = std::min(d, d2);
	}
	else if (line.getAxis() == Axis::y)
	{
		d = std::abs(line.getLimit() - box.m_min.y);
		d2 = std::abs(line.getLimit() - box.m_max.y);
		r = std::min(d, d2);
	}
	return r;
}

//PhysicEngine calculate Distance

//PhysicEngine Response

void PhysicEngine::collisionResponseX(AABBbox* box, AABBbox* box2)
{
	float v, v2;
	//v = ((box->getMass() - box2->getMass()) / (box->getMass() + box2->getMass())*box->getV().x) + ((2 * box2->getMass()) / (box->getMass() + box2->getMass())*box2->getV().x);
	//v2 = ((box->getMass() * box->getV().x) + (box2->getMass() * box2->getV().x) - (box->getMass() * v))/(box2->getMass());
	v = 0.0f;
	v2 = 0.0f;
	box->setV({ v, box->getV().y });
	//box2->setV({ v2, box2->getV().y });
}
void PhysicEngine::collisionResponseY(AABBbox* box, AABBbox* box2)
{
	float v, v2;
	v = 0;
	v2 = 0;
	box->setV({ box->getV().x, v });
	//box2->setV({ box2->getV().x, v2 });
}

//PhysicEngine Response

//PhysicEngine CollisionResolution

float PhysicEngine::collisionResolutionX(AABBbox& box, AABBbox& box2)
{
	return 0.0f;
}

float PhysicEngine::collisionResolutionY(AABBbox& box, AABBbox& box2)
{
	return 0.0f;
}


//PhysicEngine CollisionResolution

//PhysicEngine InLimit
bool PhysicEngine::inLimitX(const AABBbox& box)
{
	return true;
}
bool PhysicEngine::inLimitY(const AABBbox& box)
{
	return true;
}
//PhysicEngine InLimit

//PhysicEngine Class