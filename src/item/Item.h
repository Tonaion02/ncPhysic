#pragma once

#include "PrecompiledHeaders.h"

#include "Image.h"





enum TypeItem
{
	NullTypeItem = 0,
	Pcr = 1
};





class Item
{
public:
	Item() {}
	Item::Item(TypeItem type, uint32_t count)
		:m_type(type), m_count(count) {}

	virtual bool use() { return true; }
	virtual void drop() {}
	virtual void move() {}

	TypeItem getType() const { return m_type; }
	uint32_t getCount() const { return m_count; }
	Image& getImage() { return m_image; }

protected:
	TypeItem m_type;
	uint32_t m_count = 0;
	Image m_image;

	//TROVARE MODO PER DARE UNA POSIZIONE AGLI ITEM NELL'INVENTARIO
};





//class HealingItem : public Item
//{
//	friend Item;
//public:
//	HealingItem() {}
//	//HealingItem(TypeItem type) :Item(type) {}
//
//protected:
//	uint32_t heal;
//	
//};





enum TypePcrItem
{
	NullTypePcrItem = 0,
	Pcr1,
	Pcr2,
	Pcr3 
};





class PcrItem : public Item
{
	friend Item;
public:
	PcrItem() {}
	PcrItem(uint32_t count, const std::string& fileName, TypePcrItem code) : Item(TypeItem::Pcr, count), m_code(code) {}

	virtual bool use() override { return true; }
	virtual void drop() override {}
	virtual void move() override {}

	TypePcrItem m_code;
protected:

};