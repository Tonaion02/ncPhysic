#pragma once

#include "PrecompiledHeaders.h"





class CoolDownKey
{
public:
	CoolDownKey() {}
	CoolDownKey(double coolDown) : m_coolDown(coolDown) {}
	
	void registerKey() { m_start = std::chrono::high_resolution_clock::now(); };
	bool isEnd() 
	{
		std::chrono::time_point<std::chrono::high_resolution_clock> end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> elapsedTime = end - m_start;
		if(elapsedTime.count() >= m_coolDown)
			return true;
		return false;
	}

private:
	std::chrono::time_point<std::chrono::high_resolution_clock> m_start;
	double m_coolDown;
};