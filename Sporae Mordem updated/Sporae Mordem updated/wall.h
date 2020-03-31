#pragma once
#include "LevelManager.h"

class wall
{
private:
	SDL_Rect w_dst;
	int type;
	int TextureID;
public:
	wall(int x, int y, int type, int id);
	void render();
	SDL_Rect* getRect();
	~wall();
};

