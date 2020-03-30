#pragma once
#include "LevelManager.h"
class LoadZone
{
private:
	SDL_Rect z_dst;
	int nextZone;
	bool on;
	int wall;
	int sound;
public:
	LoadZone(int x, int y, int in, int in2, int soundID);
	~LoadZone();
	int getNext();
	void render();
	void update();
	void setPlayerPosition(SDL_Rect* oldpos);
	SDL_Rect* getRect();
};

