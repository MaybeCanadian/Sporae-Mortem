#pragma once
#include "basic_includes.h"
#include "Map.h"
#include "SoundManager.h"

class SoundManager;
class Enemy
{
private:
	SDL_Rect m_dst; //the size and position of the enemy
	double rotation; //the current rotation of the enemy
	vector<SDL_Rect> wallVec;
	double soundDetectRadius; //sound radius in pixels
public:
	Enemy(vector<SDL_Rect>);
	~Enemy();
	double const getSoundRadius();
	void update(); //update fucntion for enemy
	void render(); //render fucntion for enemy
	SDL_Rect const getRect(); //returns rect that defines the enemy
	double const getRotation(); //returns the rotation of the enemy
	void turnRight();
	bool check(char);
	void move();
	void turnLeft();
};

