#pragma once
#include "basic_includes.h"
class CollisionManager
{
	CollisionManager();
public:
	static CollisionManager& getInstance();
	~CollisionManager();
	bool AABBcollide(SDL_Rect* rect1, SDL_Rect* rect2); //takes two sdl_rects and returns if they are colliding
	bool CircleCollide(SDL_Rect* rect1, double radius1, SDL_Rect* rect2, double radius2); //takes two sdl rects and two raidus
};

