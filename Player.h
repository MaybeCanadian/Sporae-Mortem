#pragma once
#include "Engine.h"
#include "basic_includes.h"
#include <math.h>
#include "Map.h"
#include "TextureManager.h"

class TextureManager;
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
	vector<SDL_Rect> wallVec;
	int TextureID;
	string texture;
public:
	Player(vector<SDL_Rect>);
	~Player();
	void setControlType(int);
	void setKeybinds(SDL_Scancode*);
	void setDefaultinds();
	void setWallVec(vector<SDL_Rect>);
	SDL_Rect getRect();
	double getRotation();
	void update(); //this is the update fucntin called for the player
	void render();//This will be the render fucntion called by the engine's update function
	bool check(char);
	bool touchEnemy(SDL_Rect);
	void respawn();
};

