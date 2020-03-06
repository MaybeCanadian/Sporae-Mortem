#pragma once
#include "ProjectileManager.h"

class Rock
{
private:
	SDL_Rect pos;
	double rotation;
	bool r_active;
	int speed;
public:
	Rock(int x, int y, double rot);
	void update();
	bool getActive();
	void render();
	~Rock();
};

