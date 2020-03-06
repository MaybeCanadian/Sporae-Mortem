#pragma once
#include "LevelManager.h"
class LoadZone
{
private:
	SDL_Rect z_dst;
	int nextZone;
public:
	LoadZone(int x, int y, int in);
	~LoadZone();
	int getNext();
};

