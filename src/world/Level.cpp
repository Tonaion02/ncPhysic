#include "Level.h"





//Class Tile
Tile::Tile(uint32_t imType, uint32_t realType, uint32_t z)
	:m_imType(imType), m_realType(realType), m_z(z)
{

}
//Class Tile



//Class Level
Level::typeTileForLevel::typeTileForLevel(uint32_t imType, uint32_t realType)
	:imType(imType), realType(realType)
{

}

//Level Constructor
Level::Level(const std::string& fileName, uint32_t tileX, uint32_t tileY, const std::string& filePath, bool construct)
{
	std::vector<std::string> lines = getlines(fileName);

	m_maxX = 0;
	m_maxY = 0;
	m_maxZ = 0;

	std::vector<MapTile> mapTiles;
	std::vector<typeTileForLevel> typeTileSet;
	std::vector<std::string> listNamePng;

	//Extracting info about level
	std::string& line = lines[0];
	for (int i=0;i<lines.size();i++)
	{
		line = lines[i];
		if (line.find("//") == -1)
		{
			//Set name of Level
			if (line.find("levelname=") != std::string::npos)
			{
				m_name = stride(line, "levelname=");
			}
			//Set name of Level

			//Set Widht of Level
			else if (line.find("width=") != std::string::npos)
			{
				m_maxX = std::stoi(stride(line, "width="));
			}
			//Set Widht of Level

			//Set Height of Level
			else if (line.find("height=") != std::string::npos)
			{
				m_maxY = std::stoi(stride(line, "height="));
			}
			//Set Height of Level

			//Take image of Tile
			else if (line.find("imagetile=") != std::string::npos)
			{
				std::string s = line.substr(line.find("(")+1, line.size() - line.find("("));
				listNamePng.push_back(remove(s, ")"));
			}
			//Take image of Tile

			else if (line.find("interagibletile=") != std::string::npos)
			{
				std::string s = stride(line, "interagibletile=(");
				s = remove(s, ")");
				std::vector<std::string> str = split(s, ",");
				m_interagibleTiles[{std::stoi(str[0]), std::stoi(str[1])}] = InteragibleTile(std::stoi(str[2]));
			}

			//Excract Type Tile
			else if (line.find("tile=") != std::string::npos)
			{
				std::string s = line.substr(line.find("(")+1, line.size() - line.find("("));
				s = remove(s, ")");
				std::vector<std::string> t = split(s, ",");
				typeTileSet.push_back(typeTileForLevel(std::stoi(t[0]), std::stoi(t[1])));
			}
			//Excract Type Tile

			//Set MapTile of Level
			else if (line.find("maptile") != std::string::npos)
			{
				m_tileBuffer = MapTile(m_maxX, m_maxY);

				i++;
				if (i >= lines.size())
					break;
				line = lines[i];

				int y = 0, x = 0;

				while (!line.find("]") != std::string::npos)
				{
					if (line.find("//") == -1)
					{
						if (line.find("(") != std::string::npos)
						{
							y = 0;
							x = 0;
							mapTiles.push_back(MapTile(m_maxX, m_maxY));
						}

						else if (line.find(")") != std::string::npos)
						{
							m_maxZ++;
						}

						else if (line.find(",") != std::string::npos)
						{
							std::vector<std::string> t = split(line, ",");

							for (x = 0; x < m_maxX; x++)
							{
								//if(typeTileSet[std::stoi(t[x])].realType)
									mapTiles[m_maxZ][y][x] = Tile(typeTileSet[std::stoi(t[x])].imType, typeTileSet[std::stoi(t[x])].realType, m_maxZ);
							}

							y++;
						}

						i++;
						if (i >= lines.size())
							break;
						line = lines[i];
					}
				}
			}
			//Set MapTile of Level
		}
	}
	//Extracting info about level

	//Create StaticImage
	if (construct)
	{
		std::vector<StaticImage> staticImages(m_maxZ);
		for (int i = 0; i < staticImages.size(); i++)
		{
			staticImages[i] = StaticImage(tileX * m_maxX, tileY * m_maxY);
		}

		std::vector<StaticImage> staticTileImages;
		for (int i = 0; i < listNamePng.size(); i++)
		{
			staticTileImages.push_back(StaticImage(filePath + "../images/" + listNamePng[i]));
		}

		for (int h = 0; h < m_maxZ; h++)
		{
			for (int j = 0; j < m_maxY; j++)
			{
				for (int i = 0; i < m_maxX; i++)
				{
					Tile t = mapTiles[h][j][i];
					if (h < 1 || t.m_realType > 0)
					{
						staticImages[t.m_z].blit(i * tileX, j * tileY, staticTileImages[t.m_imType]);
						//m_tileBuffer[j][i] = t;
					}
						
				}
			}
		}

		for (int i = 0; i < staticImages.size(); i++)
		{
			staticImages[i].setFileName(filePath + std::to_string(i) + ".png");
			staticImages[i].save();
		}
	}

	for (int h = 0; h < m_maxZ; h++)
	{
		for (int j = 0; j < m_maxY; j++)
		{
			for (int i = 0; i < m_maxX; i++)
			{
				Tile t = mapTiles[h][j][i];
				if (h < 1 || t.m_realType > 0)
				{
					//staticImages[t.m_z].blit(i * tileX, j * tileY, staticTileImages[t.m_imType]);
					m_tileBuffer[j][i] = t;
				}

			}
		}
	}

	for (int i = 0; i < m_maxZ; i++)
	{
		//m_textures.push_back(nctl::makeUnique<nc::Texture>((filePath + std::to_string(i) + ".png").c_str()));
		TextureLoader::loadTexture(filePath + std::to_string(i) + ".png");
		m_images.push_back(Image(TextureLoader::getTexture(filePath + std::to_string(i) + ".png"), Renderer::getLayer(0)));
	}
	//Create StaticImage
}
//Level Constructor

//Class Level