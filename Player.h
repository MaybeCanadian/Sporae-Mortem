#pragma once
#include "Engine.h"
#include "basic_includes.h"
#include <math.h>


class Player
{
private:
	bool m_active;
	int speed;
	SDL_Rect m_dst;
	SDL_Scancode keybinds[4]; //up, down, left, right
	void keyboardmovement(SDL_Scancode*);
	void controllermovement();
	int control_type;
	double rotation;
	void mousemovement();
	int mouseX;
	int mouseY;

public:
	Player();
	~Player();
	void setControlType(int);
	void setKeybinds(SDL_Scancode*);
	void setDefaultinds();
	SDL_Rect getRect();
	double getRotation();
	void update(); //this is the update fucntin called for the player
	void render();//This will be the render fucntion called by the engine's update function
};

