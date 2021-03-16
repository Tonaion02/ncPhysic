#include "Player.h"





//Class Player

Player* Player::player = new Player();

Player::Player(const std::string& fileName)
{
	player->fileName = fileName;
	std::vector<std::string> lines = getlines(fileName);

	for (int i = 0; i < lines.size(); i++)
	{
		std::string& line = lines[i];
		if (!isCommentLine(line))
		{
			if (findInString(line, "pos="))
			{
				line = stride(line, "pos=(");
				line = remove(line, ")");
				std::vector<std::string> str = split(line, ",");
				player->pos.x = std::stoi(str[0]);
				player->pos.y = std::stoi(str[1]);
			}
		}
	}

	player->statusGame = StatusGame::exploring;
	player->statusMoving = StatusMoving::stop;
	player->direction = Direction::down;
	player->statusStaticAnimation = StatusStaticAnimation::end;

	//Aggiungere staticImage
	
	player->posImage.x = player->pos.x * Options::getInstance().getTileWidht() + (Options::getInstance().getTileWidht() / 2);
	player->posImage.y = player->pos.y * Options::getInstance().getTileHeight() + (Options::getInstance().getTileHeight() / 2);

	player->item = PcrItem(0, "", TypePcrItem::NullTypePcrItem);

	//player->movingAnimation[0] = (DinamicAnimation({ "../triEngine-data/data/images/surfer.png" , "../triEngine-data/data/images/surfForBlit2.png" }, 0.5f, player->posImage, 2, 1.0f, { 0, (int)-Options::getInstance().getTileHeight() }));
	//player->movingAnimation[1] = (DinamicAnimation({ "../triEngine-data/data/images/surfer.png" , "../triEngine-data/data/images/surfForBlit2.png" }, 0.5f, player->posImage, 2, 1.0f, { 0, (int)Options::getInstance().getTileHeight() }));
	//player->movingAnimation[2] = (DinamicAnimation({ "../triEngine-data/data/images/surfer.png" , "../triEngine-data/data/images/surfForBlit2.png" }, 0.5f, player->posImage, 2, 1.0f, { (int)-Options::getInstance().getTileWidht() , 0 }));
	//player->movingAnimation[3] = (DinamicAnimation({ "../triEngine-data/data/images/surfer.png" , "../triEngine-data/data/images/surfForBlit2.png" }, 0.5f, player->posImage, 2, 1.0f, { (int)Options::getInstance().getTileWidht(), 0 }));
	
	player->movingAnimation = std::vector<DinamicAnimation>(4);
	player->movingAnimation[0] = (DinamicAnimation({ "../triEngine-data/data/images/pg.png" , "../triEngine-data/data/images/pg.png" }, 0.5f, player->posImage, 2, 1.0f, { 0, (int)-Options::getInstance().getTileHeight() }));
	player->movingAnimation[1] = (DinamicAnimation({ "../triEngine-data/data/images/pg.png" , "../triEngine-data/data/images/pg.png" }, 0.5f, player->posImage, 2, 1.0f, { 0, (int)Options::getInstance().getTileHeight() }));
	player->movingAnimation[2] = (DinamicAnimation({ "../triEngine-data/data/images/pg.png" , "../triEngine-data/data/images/pg.png" }, 0.5f, player->posImage, 2, 1.0f, { (int)-Options::getInstance().getTileWidht() , 0 }));
	player->movingAnimation[3] = (DinamicAnimation({ "../triEngine-data/data/images/pg.png" , "../triEngine-data/data/images/pg.png" }, 0.5f, player->posImage, 2, 1.0f, { (int)Options::getInstance().getTileWidht(), 0 }));


	player->staticAnimation = std::vector<StaticAnimation>(4);
	player->staticAnimation[0] = (StaticAnimation({ "../triEngine-data/data/images/pg.png" , "../triEngine-data/data/images/pg.png" }, 0.5f, player->posImage, 2));
	player->staticAnimation[1] = (StaticAnimation({ "../triEngine-data/data/images/pg.png" , "../triEngine-data/data/images/pg.png" }, 0.5f, player->posImage, 2));
	player->staticAnimation[2] = (StaticAnimation({ "../triEngine-data/data/images/pg.png" , "../triEngine-data/data/images/pg.png" }, 0.5f, player->posImage, 2));
	player->staticAnimation[3] = (StaticAnimation({ "../triEngine-data/data/images/pg.png" , "../triEngine-data/data/images/pg.png" }, 0.5f, player->posImage, 2));
}

void Player::collecting()
{
	if (player->staticAnimation[player->direction].isEnd())
	{
		player->statusStaticAnimation = StatusStaticAnimation::end;
		return;
	}
	player->staticAnimation[player->direction].animate();
}

void Player::tryToInteract(const Level& level)
{
	const std::unordered_map<nc::Vector2i, InteragibleTile, std::MyHashFunction>& interagibleTiles = level.getInteragibleTiles();

	nc::Vector2i t = player->pos;

	switch (player->direction)
	{
	case Direction::top:
		t.y += -1;
		break;

	case Direction::down:
		t.y += 1;
		break;

	case Direction::left:
		t.x += -1;
		break;

	case Direction::right:
		t.x += 1;
		break;
	}

	//MAGARI POSSO SOSTITUIRE CON LA CHIAMATA A MENU E COSE SIMILI
	if (interagibleTiles.find(t) != interagibleTiles.end())
	{
		player->item = PcrItem(1, "", (TypePcrItem)interagibleTiles.find(t)->second.getIdItem());
		player->statusStaticAnimation = StatusStaticAnimation::collect;
		player->staticAnimation[player->direction].start();
	}
	
}

bool Player::controllMove(const Level& level, const nc::Vector2i p)
{
	if ((p.x >= level.getMaxX() || p.x < 0) || (p.y < 0 || p.y >= level.getMaxY()))
		return false;

	const MapTile& mapTile = level.getMapTile();
	uint32_t tipo = mapTile[p.y][p.x].m_realType;

	switch (mapTile[p.y][p.x].m_realType)
	{
	case TypeLogicTile::Ground:
		break;

	case TypeLogicTile::Water:
		break;

	case TypeLogicTile::Wall:
		return false;
		break;
	}

	return true;
}

void Player::startMove(const Level& level)
{
	nc::Vector2i t = player->pos;

	switch (player->direction)
	{
	case Direction::top:
		t.y += -1;
	break;

	case Direction::down:
		t.y += 1;
	break;

	case Direction::left:
		t.x += -1;
	break;

	case Direction::right:
		t.x += 1;
	break;
	}

	if(player->controllMove(level, t))
	{
		player->pos = t;

		player->statusMoving = StatusMoving::moving;
		player->movingAnimation[player->direction].setPos(player->posImage);
		player->movingAnimation[player->direction].start();
	}

}

void Player::move()
{
	if (player->statusMoving == StatusMoving::moving)
	{
		if (!player->movingAnimation[player->direction].isEnd())
		{
			player->movingAnimation[player->direction].animate();
			player->posImage = player->movingAnimation[player->direction].getPos();
		}
		else
		{
			player->statusMoving = StatusMoving::stop;
			player->posImage.x = player->pos.x * Options::getInstance().getTileWidht() + (Options::getInstance().getTileWidht()/2); 
			player->posImage.y = player->pos.y * Options::getInstance().getTileHeight() + (Options::getInstance().getTileHeight()/2);
		}
	}
}

Image& Player::getImage()
{
	if (player->statusStaticAnimation == StatusStaticAnimation::collect)
	{
		return player->staticAnimation[player->direction].getImage();
	}

	if (player->statusMoving == StatusMoving::moving)
	{
		return player->movingAnimation[player->direction].getImage();
	}

	return player->movingAnimation[player->direction].getImage();
}

void Player::updateDirection(Direction dir)
{
	player->direction = dir;
}

void Player::saveGame()
{
	std::vector<std::string> lines;

	std::string newline = "\n";

	lines.push_back("pos=(" + std::to_string(player->pos.x) + "," + std::to_string(player->pos.y) + ")" + newline);

	savelines(player->fileName, lines);
}
//Class Player