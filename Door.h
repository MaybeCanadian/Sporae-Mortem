#pragma once
#include "LockedManager.h"

class Door
{
private:
	SDL_Rect pos;
	bool locked;
	int type, textureID;
	int nextzone;
public:
	Door(int x, int y, int in,int zone, int id);
	void unlock();
	void render();
	SDL_Rect* getRect();
	bool getLocked();
	void update();
	~Door();
};

