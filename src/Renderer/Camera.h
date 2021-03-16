#pragma once

#include "PrecompiledHeaders.h"

#include <ncine/Application.h>





namespace nc = ncine;

class Camera
{
public:
	
	struct RenderData
	{
		RenderData(int32_t xI, int32_t yI, int32_t xE, int32_t yE) :xI(xI), yI(yI), xE(xE), yE(yE) {}

		int32_t xI, yI, xE, yE;
	};

	Camera() {}
	Camera(int32_t posX, int32_t posY, int32_t levelWidth, int32_t levelHeight);
	Camera(const nc::Vector2i& pos, const nc::Vector2i& levelDimension);

	static RenderData renderingInfo();

	static nc::Vector2i getCameraPosInProspective();
	static nc::Vector2i getPosFromCamera(const nc::Vector2i& Pos);
	static nc::Vector2i getPosFromCamera(int32_t posX, int32_t posY);

	static void updatePosX(int32_t posX) { pos.x = posX; }
	static void updatePosY(int32_t posY) { pos.y = posY; }
	static void updatePos(nc::Vector2i pos) { Camera::pos = pos; }

	static int32_t getPosX() { return pos.x; }
	static int32_t getPosY() { return pos.y; }
	static nc::Vector2i getPos() { return pos; }
	static uint32_t getAdjWidth() { return adj.x; }
	static uint32_t getAdjHeight() { return adj.y; }
	static nc::Vector2i getAdj() { return adj; }

private:
	static nc::Vector2i levelDimension;
	static nc::Vector2i pos;
	static nc::Vector2i adj;
};