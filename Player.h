#pragma once
#include "PlayerManager.h"

class Player
{
private:
	bool m_active;
	SDL_Rect m_dst, future;
	int control_type, textureID, speed;
	SDL_Scancode keybinds[4]; //up, down, left, right
	double rotation;
	int mouseX, mouseY;
	std::string texture;

private:
	void keyboardmovement(); //movement for keyboard control
	void controllermovement(); //moveent for controller not added
	void moveUP(); //move up
	void moveDOWN(); //move down
	void moveRIGHT(); //move right
	void moveLEFT(); //move left
	void mouseAttack();

public:
	Player(int x, int y, int type);
	~Player();
	void setControlType(int); //sets control type between keyboard and controller
	void setKeybinds(SDL_Scancode*); //sets the binds to the input
	void setDefaultinds(); //sets the binds to default
	SDL_Rect* getRect(); //returns the rectangle
	double getRotation(); //returns rotation
	void update(); //this is the update fucntin called for the player
	void render();//This will be the render fucntion called by the engine's update functio
	void respawn(); //respawns at last spawn point
};