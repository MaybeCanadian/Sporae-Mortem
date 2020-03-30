#include "LoadZone.h"



LoadZone::LoadZone(int x, int y, int in, int in2, int soundID)
{
	z_dst = { x, y, GRID, GRID };
	nextZone = in;
	std::cout << "making loadzone to zone " << nextZone << std::endl;
	wall = in2;
	sound = soundID;
}

LoadZone::~LoadZone()
{
}

int LoadZone::getNext()
{
	return nextZone;
}

void LoadZone::render()
{
	TextureManager::getInstance().SetDrawColor(0, 0, 0, 255);
	TextureManager::getInstance().FillRect(&z_dst);
}

void LoadZone::update()
{
	if (LevelManager::getInstance().getOnloadZone() == false)
	{
		for (int i = 0; i < ObjectManager::getInstance().getPlayerManager()->getNumPlayers(); i++)
		{
			if (UTIL::AABBcollide(&z_dst, ObjectManager::getInstance().getPlayerManager()->getPlayers(i)->getRect()))
			{
				AudioManager::getInstance().playSound(sound, -1, 0);
				setPlayerPosition(ObjectManager::getInstance().getPlayerManager()->getPlayers(i)->getRect());
				LevelManager::getInstance().setOnloadZone(true);
				LevelStateManager::getInstance().changeLevel(nextZone);
			}
		}
	}
}

void LoadZone::setPlayerPosition(SDL_Rect* oldpos)
{
	SDL_Point newpos = { 0, 0 };

	switch (wall)
	{
	case 0:
		std::cout << "wall 0\n";
		newpos.y = HEIGHT - oldpos->h;
		newpos.x = z_dst.x;
		break;
	case 1:
		std::cout << "wall 1\n";
		newpos.x = 0 + oldpos->w;
		newpos.y = oldpos->y;
		break;
	case 2:
		std::cout << "wall 2\n";
		newpos.y = 0 + oldpos->h;
		newpos.x = oldpos->x;
		break;
	case 3:
		std::cout << "wall 3\n";
		newpos.x = WIDTH - oldpos->w;
		newpos.y = oldpos->y;
		break;
	}

	ObjectManager::getInstance().getPlayerManager()->setPlayerPositions(newpos.x, newpos.y);
}

SDL_Rect * LoadZone::getRect()
{
	return &z_dst;
}
