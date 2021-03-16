#pragma once

#include "PrecompiledHeaders.h"
#include "Renderer/Options.h"
#include "AddonsString.h"

#include "Animation/Animation.h"

#include "world/LogicTile.h"
#include "world/Level.h"

#include "item/Item.h"

#include <ncine/Vector2.h>





namespace nc = ncine;

class Player
{
public:
	friend StaticAnimation;
	friend DinamicAnimation;

	enum Direction
	{
		NullDirection = -1,
		top = 0, 
		down = 1,
		left = 2,
		right = 3
	};

	enum StatusMoving
	{
		NullStatusMoving = -1,
		stop = 0,
		moving = 1
	};

	enum StatusStaticAnimation
	{
		NullStatusStaticAnimation = -1,
		end = 0,
		collect = 1
	};

	enum StatusGame
	{
		NullStatusGame = -1,
		exploring = 0,
		battle = 1,
		menu = 2
	};

public:
	Player() {}
	Player(const std::string& fileName);

	static void updateDirection(Direction dir);

	static void updatePos(nc::Vector2i pos) { player->pos = pos; }
	static void updatePosX(int32_t x) { player->pos.x = x; }
	static void updatePosY(int32_t y) { player->pos.y = y; }

	static void updateStatusGame(StatusGame statusGame) { player->statusGame = statusGame; }

	static nc::Vector2i getPosImage() { return player->posImage; }

	static Image& getImage();

	static nc::Vector2i getPos() { return player->pos; }
	static int32_t getPosX() { return player->pos.x; }
	static int32_t getPosY() { return player->pos.y; }

	static StatusGame getStatusGame() { return player->statusGame; }
	static StatusMoving getStatusMoving() { return player->statusMoving; }
	static StatusStaticAnimation getStatusStaticAnimation() { return player->statusStaticAnimation; }

	static void startMove(const Level& level);
	static void move();

	static void tryToInteract(const Level& level);
	static void collecting();

	static void saveGame();

	//da eliminare(for testing)
	static const PcrItem& getPcrItem() { return player->item; }
	PcrItem item;

private:
	static bool controllMove(const Level& level, const nc::Vector2i p);

private:
	nc::Vector2i pos;
	nc::Vector2i posImage;

	std::string fileName;

	StatusGame statusGame;

	StatusStaticAnimation statusStaticAnimation;
	std::vector<StaticAnimation> staticAnimation;

	Direction direction;
	std::vector<DinamicAnimation> movingAnimation;

	StatusMoving statusMoving;

	std::vector<Image> staticImage;

	static Player* player;
};