#pragma once
#include "ProjectileManager.h"

class Rock
{
private:
	SDL_Rect pos, future;
	double rotation;
	bool r_active;
	int speed;
	int soundthrow, soundhit;
	int texture;

public:
	Rock(int x, int y, double rot, int s1, int s2, int t1);
	void update();
	bool getActive();
	void render();
	~Rock();
};

