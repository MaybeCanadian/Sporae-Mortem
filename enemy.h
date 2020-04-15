#pragma once
#include "EnemyManager.h"

enum {
	hunt, search, wander
};

class enemy
{
private:
	SDL_Rect m_dst;
	SDL_Point nearSound, nearPlayer;
	double lookRange, rotation;
	std::vector<SDL_Point> path;
	SDL_Point pathtarget;
	int textureID;
	int type;
	int speed, MaxVelocity, MaxForce;
	SDL_Point currentVelocity, SteeringForce, desiredVelocity;
	double angle;

	int state;

private:
	bool look(SDL_Point* nearPlayer);
	bool listen(SDL_Point* nearSound);
	bool checkwalls(SDL_Point* players);

	bool followpath();
	void seek(SDL_Point* target);
	bool move(SDL_Point* pos);
	bool moveVelocity(SDL_Point* target);
	double limitspeed(SDL_Point* target);

	bool AI();
	bool wandering();
	bool hunting();
	bool searching();

public:
	enemy(int x, int y, int type, int id);
	void update();
	void render();
	void clearpath();
	~enemy();
};

