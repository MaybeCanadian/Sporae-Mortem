#include "Door.h"

Door::Door(int x, int y, int in,int zone, int id)
{
	pos = { x, y, GRID, GRID };
	type = in;
	textureID = id;
	nextzone = zone;
	locked = true;
}

void Door::unlock()
{
	locked = false;
	//play noise
}

void Door::update()
{
	if (locked == false)
	{
		for (int i = 0; i < ObjectManager::getInstance().getPlayerManager()->getNumPlayers(); i++)
		{
			if (UTIL::AABBcollide(&pos, ObjectManager::getInstance().getPlayerManager()->getPlayers(i)->getRect()))
			{
				LevelStateManager::getInstance().changeLevel(nextzone);
			}
		}
	}
}

void Door::render()
{
	if(locked == true)
		TextureManager::getInstance().Draw(textureID, NULL, &pos);
}

SDL_Rect * Door::getRect()
{
	return &pos;
}

bool Door::getLocked()
{
	return locked;
}

Door::~Door()
{
}
