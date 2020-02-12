#pragma once
#include "basic_includes.h"

class Rock
{
private:
	SDL_Rect m_dst;
	double unitVecX;
	double unitVecY;
	int speed;
public:
	Rock(double rotation, SDL_Rect player);
	~Rock();
	void update();
	void render();
};

