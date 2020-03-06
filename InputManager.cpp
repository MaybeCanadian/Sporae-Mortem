#include "InputManager.h"



InputManager::InputManager()
{
}

InputManager & InputManager::getInstance()
{
	static InputManager instance;
	return instance;
}

bool InputManager::KeyDown(SDL_Scancode c)
{
		if (g_iKeystates != nullptr)
	{
		if (g_iKeystates[c] == 1)
			return true;
		else return false;
	}
	else return false;
}

bool InputManager::initManager()
{
	g_iKeystates = SDL_GetKeyboardState(nullptr);
	mouse = { 0, 0 };
	std::cout << "inputManager init.\n";
	return true;
}

void InputManager::clean()
{
	std::cout << "inputManager clean.\n";
}

SDL_Point * InputManager::getMouse()
{
	SDL_GetMouseState(&mouse.x, &mouse.y);
	return &mouse;
}

bool InputManager::getMouseState(int i)
{
	return mousestate[i];
}

void InputManager::mouseDown(SDL_MouseButtonEvent & input)
{
	switch (input.button)
	{
	case SDL_BUTTON_LEFT:
		mousestate[0] = true;
		mouseclick[0] = true;
		break;
	case SDL_BUTTON_MIDDLE:
		mousestate[1] = true;
		mouseclick[1] = true;
		break;
	case SDL_BUTTON_RIGHT:
		mousestate[2] = true;
		mouseclick[2] = true;
		break;
	}
}

void InputManager::mouseUp(SDL_MouseButtonEvent & input)
{
	switch (input.button)
	{
	case SDL_BUTTON_LEFT:
		mousestate[0] = false;
		break;
	case SDL_BUTTON_MIDDLE:
		mousestate[1] = false;
		break;
	case SDL_BUTTON_RIGHT:
		mousestate[2] = false;
	}
}

bool InputManager::getMouseClick(int i)
{
	return mouseclick[i];
}

void InputManager::update()
{
	for (int i = 0; i < (int)sizeof(mouseclick); i++)
		if (mouseclick[i] == true)
			mouseclick[i] = false;
}

InputManager::~InputManager()
{
}
