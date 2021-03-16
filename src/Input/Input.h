#pragma once

#include "PrecompiledHeaders.h"

#include <ncine/Application.h>
#include <ncine/Keys.h>
#include <ncine/InputEvents.h>





namespace nc = ncine;

class Input
{
public:
	enum KeyMouse
	{
		NullKeyMouse = -1,
		leftKey = 0,
		middleKey = 1,
		rightKey = 2
	};

public:
	Input() {};

	static void saveEvent(const nc::KeyboardEvent& event);
	static void deleteEvent(const nc::KeyboardEvent& event);
	static bool isPressed(const nc::KeySym& event);
	static bool isRealesed(const nc::KeySym& sym);

	static void saveEvent(const nc::MouseEvent& event);
	static void deleteEvent(const nc::MouseEvent& event);
	static void clearMouseEvent();
	static bool isPressed(const KeyMouse& keyMouse);
	static bool isRealesed(const KeyMouse& keyMouse);

	static void clearReleasedKey();

	static void updateMousePos(const nc::MouseState& event);

	static nc::Vector2i getMousePos() { return s_mousePos; };
	static nc::Vector2i getMouseSliding() { return s_mouseSliding; }

private:
	static std::vector<nc::KeySym> s_keyInput;
	static std::vector<KeyMouse> s_keyMouseInput;
	static std::vector<nc::KeySym> s_releasedKey;
	static std::vector<KeyMouse> s_releasedKeyMouseInput;

	static nc::Vector2i s_lastMousePos;
	static nc::Vector2i s_mousePos;
	static nc::Vector2i s_mouseSliding;
};