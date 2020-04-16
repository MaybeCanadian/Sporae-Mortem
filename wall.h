#pragma once
#include "LevelManager.h"

class wall
{
private:
	SDL_Rect w_dst;
	SDL_Rect w_SRC;
	int TextureID;
public:
	wall(int x, int y, int type, int id);
	void render();
	SDL_Rect* getRect();
	~wall();
};

