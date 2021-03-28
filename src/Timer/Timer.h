#pragma once

#include "PrecompiledHeaders.h"





class CoolDown
{
public:
	CoolDown() {}
	CoolDown(double coolDown);

	void registerInit();
	bool isEnd();

private:
	std::chrono::time_point<std::chrono::high_resolution_clock> m_start;
	double m_coolDown;
};