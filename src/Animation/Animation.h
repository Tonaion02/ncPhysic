#pragma once

#include "PrecompiledHeaders.h"

#include "Renderer/Renderer.h"
#include "Renderer/Options.h"
#include "Renderer/Camera.h"

#include "Image.h"





class Animation
{
public:
	Animation() {}

	virtual void start() {}
	virtual void animate() {}
	virtual bool isEnd() { return !m_running; }

protected:
	bool m_running=false;
};





class StaticAnimation : public Animation
{
	friend Animation;
public:
	StaticAnimation() {}
	StaticAnimation(const std::vector<std::string>& fileNames, float time, const nc::Vector2i& pos, int32_t h);

	void start() override;
	void animate() override;

	void loop();
	bool isLoop();
	Image& getImage();
	int32_t getH();

	nc::Vector2i getPos();

protected:
	float m_time = 1.0f;
	float m_index = 0.0f;
	float m_incrementIndex = 0.0f;

	nc::Vector2i m_pos;

	int32_t m_h = 0;
	std::vector<Image> m_images;

	bool m_loop = false;
};





class DinamicAnimation : public StaticAnimation
{
	friend StaticAnimation;
public:
	DinamicAnimation() : StaticAnimation() {}
	DinamicAnimation(const std::vector<std::string>& fileNames, float timeAnimation, const nc::Vector2i& pos, int32_t h, float timeMoving, const nc::Vector2i& spaceMove);

	void animate() override;
	void start() override;

	void setPos(const nc::Vector2i pos);

protected:
	float m_timeMoving = 0.0f;

	nc::Vector2f m_posf;
	nc::Vector2i m_spaceMove;
	nc::Vector2f m_spaceIncrement;
	nc::Vector2i m_end;
};