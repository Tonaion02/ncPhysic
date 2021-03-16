#pragma once

#include "PrecompiledHeaders.h"
#include "AddonsString.h"





class Options
{
public:
	static Options& getInstance()
	{
		static Options instance;
		return instance;
	}

	void readFromFile(const std::string& fileName);
	void writeInFile();

	void setFileName(const std::string& fileName) { s_fileName = fileName; }
	void setFps(uint32_t fps) { s_fps = fps; }
	void setTileWidht(uint32_t tileWidth) { s_tileWidth = tileWidth; }
	void setTileHeight(uint32_t tileHeight) { s_tileHeight = tileHeight; }
	void setLevelWidth(uint32_t levelWidth) { s_levelWidth = levelWidth; }
	void setLevelHeight(uint32_t levelHeight) { s_levelHeight = levelHeight; }
	
	void setBaseFilePath(const std::string& baseFilePath) { s_baseFilePath = baseFilePath; }
	void setLevelFilePath(const std::string& levelFilePath) { s_levelFilePath = levelFilePath; }
	void setImageFilePath(const std::string& imageFilePath) { s_imageFilePath = imageFilePath; }

	std::string getFileName() { return s_fileName; }
	uint32_t getFps() { return s_fps; }
	uint32_t getTileWidht() { return s_tileWidth; }
	uint32_t getTileHeight() { return s_tileHeight; }
	uint32_t getLevelWidth() { return s_levelWidth; }
	uint32_t getLevelHeight() { return s_levelHeight; }
	
	std::string getBaseFilePath() { return s_baseFilePath; }
	std::string getLevelFilePath() { return s_levelFilePath; }
	std::string getImageFilePath() { return s_imageFilePath; }

protected:
	Options() :s_fps(60) {}

	Options(const Options& generalOptions) = delete;
	void operator=(const Options& generalOptions) = delete;

protected:
	uint32_t s_fps;
	uint32_t s_tileWidth, s_tileHeight;
	uint32_t s_levelWidth, s_levelHeight;
	
	std::string s_fileName;
	
	std::string s_baseFilePath;
	std::string s_levelFilePath;
	std::string s_imageFilePath;
};