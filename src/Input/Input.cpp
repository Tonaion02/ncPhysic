#include "Input.h"





//Class Input Manager

std::vector<nc::KeySym> Input::s_keyInput;
std::vector<Input::KeyMouse> Input::s_keyMouseInput;

std::vector<nc::KeySym> Input::s_releasedKey;
std::vector<Input::KeyMouse> Input::s_releasedKeyMouseInput;

nc::Vector2i Input::s_mousePos;

nc::Vector2i Input::s_lastMousePos = { 0,0 };
nc::Vector2i Input::s_mouseSliding = { 0,0 };

void Input::saveEvent(const nc::KeyboardEvent& event)
{
	s_keyInput.push_back(event.sym);
}

void Input::saveEvent(const nc::MouseEvent& event)
{
	KeyMouse keyMouse;
	if (event.isLeftButton())
	{
		keyMouse = KeyMouse::leftKey;
	}
	else if (event.isRightButton())
	{
		keyMouse = KeyMouse::rightKey;
	}
	else if (event.isMiddleButton())
	{
		keyMouse = KeyMouse::middleKey;
	}

	s_keyMouseInput.push_back(keyMouse);
}

void Input::updateMousePos(const nc::MouseState& event)
{
	s_lastMousePos = s_mousePos;
	//s_mousePos = { event.x, (int32_t)(nc::theApplication().height() - event.y) };
	s_mousePos = { event.x, event.y };
	s_mouseSliding = s_mousePos - s_lastMousePos;
}

void Input::deleteEvent(const nc::KeyboardEvent& event)
{
	for (int i = 0; i < s_keyInput.size(); i++)
	{
		if (s_keyInput[i] == event.sym)
		{
			s_keyInput.erase(s_keyInput.begin() + i);
		}
	}
	
	s_releasedKey.push_back(event.sym);
}

void Input::deleteEvent(const nc::MouseEvent& event)
{
	KeyMouse keyMouse;
	if (event.isLeftButton())
	{
		keyMouse = KeyMouse::leftKey;
	}
	else if (event.isRightButton())
	{
		keyMouse = KeyMouse::rightKey;
	}
	else if (event.isMiddleButton())
	{
		keyMouse = KeyMouse::middleKey;
	}

	for (int i = 0; i < s_keyMouseInput.size(); i++)
	{
		if (s_keyMouseInput[i] == keyMouse)
		{
			s_keyMouseInput.erase(s_keyMouseInput.begin() + i);
		}
	}

	s_releasedKeyMouseInput.push_back(keyMouse);
}

void Input::clearMouseEvent()
{
	s_mouseSliding = { 0,0 };
	s_releasedKeyMouseInput.clear();
	//s_keyMouseInput.clear();
}

bool Input::isPressed(const nc::KeySym& sym)
{
	for (int i = 0; i < s_keyInput.size(); i++)
	{
		if (s_keyInput[i] == sym)
		{
			return true;
		}
	}

	return false;
}

bool Input::isPressed(const KeyMouse& keyMouse)
{
	for (int i = 0; i < s_keyMouseInput.size(); i++)
	{
		if (s_keyMouseInput[i] == keyMouse)
		{
			return true;
		}
	}

	return false;
}

bool Input::isRealesed(const nc::KeySym& sym)
{
	for (int i = 0; i < s_releasedKey.size(); i++)
	{
		if (s_releasedKey[i] == sym)
		{
			return true;
		}
	}

	return false;
}

bool Input::isRealesed(const Input::KeyMouse& keyMouse)
{
	for (int i = 0; i < s_releasedKeyMouseInput.size(); i++)
	{
		if (s_releasedKeyMouseInput[i] == keyMouse)
		{
			return true;
		}
	}

	return false;
}

void Input::clearReleasedKey()
{
	s_releasedKey.clear();
}
//Class Input Manager