#pragma once

#include "PrecompiledHeaders.h"

#include "AddonsString.h"

#include "StaticImage.h"
#include "Image.h"
#include <ncine/Application.h>

#include "Renderer/Renderer.h"

#include "world/LogicTile.h"




struct Tile
{
	Tile() {}
	Tile(uint32_t imType, uint32_t realType, uint32_t z);

	uint32_t m_imType, m_realType, m_z;
};





struct MapTile : public std::vector<std::vector<Tile>>
{
	MapTile() {}
	MapTile(uint32_t n, uint32_t m)
	{
		std::vector<std::vector<Tile>>& self = *this;

		self.resize(m);
		for (int i = 0; i < m; i++)
		{
			self[i].resize(n);
		}
	}
};





class Level
{
public:
	struct typeTileForLevel
	{
		typeTileForLevel(){}
		typeTileForLevel(uint32_t imType, uint32_t realType);

		uint32_t imType, realType;
	};

	Level(){}
	Level(const std::string& fileName, uint32_t tileX, uint32_t tileY, const std::string& filePath, bool construct=true);

	const MapTile& getMapTile() const { return m_tileBuffer; }
	const std::unordered_map<nc::Vector2i, InteragibleTile, std::MyHashFunction>& getInteragibleTiles() const { return m_interagibleTiles; }

	//Info About Level
	std::string getName() const { return m_name; }

	uint32_t getMaxX() const { return m_maxX; }
	uint32_t getMaxY() const { return m_maxY; }
	uint32_t getMaxZ() const { return m_maxZ; }
	//Info About Level

	std::vector<Image> m_images;
private:
	uint32_t m_maxX, m_maxY, m_maxZ;

	std::string m_name;

	std::vector<nctl::UniquePtr<nc::Texture>> m_textures;

	MapTile m_tileBuffer;

	std::unordered_map<nc::Vector2i, InteragibleTile, std::MyHashFunction>  m_interagibleTiles;
};
