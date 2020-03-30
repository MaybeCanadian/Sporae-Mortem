#pragma once
#include "PickupManager.h"

class Key
{
private:
	SDL_Rect pos;
	int textureID;
	bool m_active;

public:
	Key(int x, int y, int type, int id);
	void update();
	void render();
	bool getActive();
	~Key();
};

