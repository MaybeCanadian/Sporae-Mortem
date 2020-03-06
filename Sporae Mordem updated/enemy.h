#pragma once
#include "EnemyManager.h"

class enemy
{
private:
	SDL_Rect m_dst;
	SDL_Point nearest;
	double detectRadius;
	double rotation;
	SDL_Point pathTarget;
public:
	enemy(int x, int y, double rotation);
	void update();
	~enemy();
};

