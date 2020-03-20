#pragma once
#include "EnemyManager.h"

class enemy
{
private:
	SDL_Rect m_dst;
	SDL_Point nearSound, nearPlayer;
	double detectRadius,lookRange, rotation;
	SDL_Point pathTarget;
	int textureID;
	int type;

private:
	bool look(SDL_Point* nearPlayer);
	bool listen(SDL_Point* nearSound);

public:
	enemy(int x, int y, int type, int id);
	void update();
	void render();
	~enemy();
};

