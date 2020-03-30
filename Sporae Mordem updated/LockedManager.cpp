#include "LockedManager.h"



LockedManager::LockedManager()
{
}

bool LockedManager::initManager()
{
	DoorTextureID = TextureManager::getInstance().addTexture("Image/lockeddoor.png");
	std::cout << "LockedManager init.\n";
	return true;
}

void LockedManager::clean()
{
	clearDoors();
	std::cout << "LockedManager cleaned.\n";
}

void LockedManager::update()
{
	if (!doors.empty())
	{
		for (int i = 0; i < (int)doors.size(); i++)
		{
			doors[i]->update();
		}
	}
}

void LockedManager::render()
{
	if (!doors.empty())
	{
		for (int i = 0; i < (int)doors.size(); i++)
		{
			doors[i]->render();
		}
	}
}

void LockedManager::clearDoors()
{
	if (!doors.empty())
	{
		for (int i = 0; i < (int)doors.size(); i++)
		{
			delete doors[i];
			doors[i] = nullptr;
		}

		doors.clear();
		doors.shrink_to_fit();
	}
}

void LockedManager::addDoor(int x, int y, int type, int nextzone)
{
	std::cout << "made a door.\n";
	doors.push_back(new Door(x, y, type, nextzone, DoorTextureID));
}

bool LockedManager::checkNearLocked(SDL_Rect * input, bool key, int type)
{
	if (!doors.empty())
	{
		for (int i = 0; i < (int)doors.size(); i++)
		{
			if (doors[i]->getLocked() == true)
			{
				if (UTIL::AABBcollide(input, doors[i]->getRect()))
				{
					if (key == true)
					{
						doors[i]->unlock();
						LevelStateManager::getInstance().setUnlocked(true);
						return false;
					}
					else
						return true;
				}
			}
		}
	}
	return false;
}

LockedManager::~LockedManager()
{
}
