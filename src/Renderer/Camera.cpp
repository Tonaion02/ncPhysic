#include "Camera.h"



//wewe

//Class Camera

nc::Vector2i Camera::pos;
nc::Vector2i Camera::adj;
nc::Vector2i Camera::levelDimension;

Camera::Camera(int32_t posX, int32_t posY, int32_t levelWidth, int32_t levelHeight)
{
	Camera::pos.x = posX;
	Camera::pos.y = posY;

	Camera::levelDimension.x = levelWidth;
	Camera::levelDimension.y = levelHeight;

	if (levelWidth < nc::theApplication().width())
		Camera::adj.x = (nc::theApplication().width() - levelWidth) / 2;
	else
		Camera::adj.x = 0;

	if (levelHeight < nc::theApplication().height())
		Camera::adj.y = (nc::theApplication().height() - levelHeight) / 2;
	else
		Camera::adj.y = 0;
}

Camera::Camera(const nc::Vector2i& pos, const nc::Vector2i& levelDimension)
{
	Camera::pos = pos;
	Camera::levelDimension = levelDimension;

	if (levelDimension.x < nc::theApplication().width())
		Camera::adj.x = (nc::theApplication().width() - levelDimension.x) / 2;
	else
		Camera::adj.x = 0;

	if (levelDimension.y < nc::theApplication().height())
		Camera::adj.y = (nc::theApplication().height() - levelDimension.y) / 2;
	else
		Camera::adj.y = 0;
}

Camera::RenderData Camera::renderingInfo()
{
	float xI, yI, xE, yE;

	xI = pos.x - nc::theApplication().width() / 2;
	yI = pos.y - nc::theApplication().height() / 2;
	xE = pos.x + nc::theApplication().width() / 2;
	yE = pos.y + nc::theApplication().height() / 2;

	if (xI < 0)
	{
		xI = 0;
		xE = nc::theApplication().width();
	}
	else if (xE > levelDimension.x)
	{
		xI = levelDimension.x - nc::theApplication().width();
		xE = levelDimension.x;
	}

	if (yI < 0)
	{
		yI = 0;
		yE = nc::theApplication().height();
	}
	else if (yE > levelDimension.y)
	{
		yI = levelDimension.y - nc::theApplication().height();
		yE = levelDimension.y;
	}

	return { (int32_t)xI, (int32_t)yI, (int32_t)xE, (int32_t)yE};
}

nc::Vector2i Camera::getCameraPosInProspective()
{
	RenderData renderData = Camera::renderingInfo();
	return { (int)(pos.x - renderData.xI + adj.x), (int)(nc::theApplication().height() - (pos.y - renderData.yI + adj.y)) };
}

nc::Vector2i Camera::getPosFromCamera(const nc::Vector2i& Pos)
{
	RenderData renderData = Camera::renderingInfo();
	return { (int)(Pos.x - renderData.xI + adj.x), (int)(nc::theApplication().height() - (Pos.y - renderData.yI + adj.y)) };
}

nc::Vector2i Camera::getPosFromCamera(int32_t posX, int32_t posY)
{
	RenderData renderData = Camera::renderingInfo();
	return { (int)(posX - renderData.xI + adj.x), (int)(posY - renderData.yI + adj.y) };
}
//Class Camera