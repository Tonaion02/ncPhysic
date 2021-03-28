#include "Timer.h"





//Timer Class

//Timer Constructor
CoolDown::CoolDown(double coolDown) : m_coolDown(coolDown)
{}
//Timer Constructor

void CoolDown::registerInit()
{
	m_start = std::chrono::high_resolution_clock::now();
}

bool CoolDown::isEnd()
{
	std::chrono::time_point<std::chrono::high_resolution_clock> end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsedTime = end - m_start;
	if (elapsedTime.count() >= m_coolDown)
		return true;
	return false;
}

//Timer Class