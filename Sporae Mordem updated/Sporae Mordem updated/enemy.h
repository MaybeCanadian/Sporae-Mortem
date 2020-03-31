#pragma once
#include "EnemyManager.h"

class enemy
{
private:
	SDL_Rect m_dst;
	SDL_Point nearSound, nearPlayer;
	double lookRange, rotation;
	std::vector<SDL_Point> path;
	SDL_Point* pathtarget;
	int textureID;
	int type;
	int speed;
	bool moving, target;

private:
	bool look(SDL_Point* nearPlayer);
	bool listen(SDL_Point* nearSound);

	bool followpath();
	bool move(SDL_Point* pos);

public:
	enemy(int x, int y, int type, int id);
	void update();
	void render();
	void clearpath();
	~enemy();
};

