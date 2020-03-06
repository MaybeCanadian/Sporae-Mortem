#pragma once
#include "LevelManager.h"

class wall
{
private:
	SDL_Rect w_dst;
	int type;
public:
	wall(int x, int y, int type);
	void render();
	~wall();
};

