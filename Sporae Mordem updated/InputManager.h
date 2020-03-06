#pragma once
#include "engine.h"

class InputManager
{
private:
	const Uint8* g_iKeystates;
	SDL_Point mouse;
	bool mousestate[3] = { false, false, false };
	bool mouseclick[3] = { false, false, false };

private:
	InputManager();

public:
	static InputManager& getInstance();
	bool KeyDown(SDL_Scancode c); //checks if a key is currently down
	bool initManager(); //inits manager
	void clean(); //cleans up manage
	SDL_Point* getMouse();
	bool getMouseState(int i); //returns the state of the mouse for buttun i
	void mouseDown(SDL_MouseButtonEvent& input); //mouse button down
	void mouseUp(SDL_MouseButtonEvent& input); //mouse button up
	bool getMouseClick(int i); //returns if a mouse of buttun i has been clicked this frame 0 is left, 1 is middle, 2 is left
	void update();
	~InputManager();
};

