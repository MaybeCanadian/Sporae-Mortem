#include "CollisionManager.h"



CollisionManager::CollisionManager()
{
}


CollisionManager & CollisionManager::getInstance()
{
	static CollisionManager Instance;
	return Instance;
}

CollisionManager::~CollisionManager()
{
}

bool CollisionManager::AABBcollide(SDL_Rect * rect1, SDL_Rect * rect2)
{
	if ((rect1->x < rect2->x + rect2->w) && (rect1->x + rect1->w > rect2->x) && (rect1->y < rect2->y + rect2->h) && (rect1->y + rect1->h > rect2->y))
		return true;
	else
		return false;
}

bool CollisionManager::CircleCollide(SDL_Rect * rect1, double radius1, SDL_Rect * rect2, double radius2)
{
	if ((sqrt(pow((rect1->x - rect2->x), 2) + pow((rect1->y - rect2->y), 2))) < (radius1 + radius2))
		return true;
	else
		return false;
}
