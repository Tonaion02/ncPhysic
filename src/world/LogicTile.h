#pragma once

#include "PrecompiledHeaders.h"

#include "ncine/Vector2.h"





namespace nc = ncine;

enum TypeLogicTile
{
	//NullTypeLogicTile = 0,
	Ground = 0,
	Water = 1,
	Wall = 2,
	Interagible = 3,
	AnimatedTile = 4
};





class LogicTile
{
public:
	LogicTile() {}

};

class UniqueLogicTile
{
public:

	UniqueLogicTile() {}

	virtual bool execute() { return true; }
};





class GroundTile : public LogicTile
{
public:
	GroundTile() {}

};

class WaterTile : public LogicTile 
{
public:
	WaterTile() {}

};

class WallTile : public LogicTile
{
public:
	WallTile() {}

};

class InteragibleTile : public UniqueLogicTile
{
public:
	InteragibleTile() {}
	InteragibleTile(int32_t idItem) : m_idItem(idItem) {}

	bool operator==(const InteragibleTile& interagibleTile) const
	{
		return m_idItem == interagibleTile.m_idItem;
	}

	int32_t getIdItem() const { return m_idItem; }

private:
	int32_t m_idItem = 0;
};

class CollectableTile : public InteragibleTile
{

};

namespace std
{
	class MyHashFunction
	{
	public:
		size_t operator()(const InteragibleTile& interagibleTile) const
		{
			return sizeof(interagibleTile.getIdItem());
		}

		size_t operator()(const nc::Vector2i& pos) const
		{
			return sizeof(pos.x) + sizeof(pos.y);
		}
	};
}