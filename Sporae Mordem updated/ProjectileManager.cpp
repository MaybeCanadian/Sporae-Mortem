#include "ProjectileManager.h"



ProjectileManager::ProjectileManager()
{
}

bool ProjectileManager::initManager()
{
	std::cout << "projectileManager init.\n";
	return true;
}

void ProjectileManager::clean()
{
	//nothing to clean yet
	std::cout << "pojectileManager clean.\n";
}

void ProjectileManager::addRock(int x, int y, double rotation)
{
	r_vRocks.push_back(new Rock(x, y, rotation));
}

void ProjectileManager::update()
{
	for (int i = 0; i < (int)r_vRocks.size(); i++)
		{
			r_vRocks[i]->update();
			if (r_vRocks[i]->getActive() == false)
			{
				delete r_vRocks[i];
				r_vRocks[i] = nullptr;
			}
		}
	
	if (!r_vRocks.empty())
	{
		for (int i = 0; i < (int)r_vRocks.size(); i++)
		{
			if (r_vRocks[i] == nullptr)
			{
				r_vRocks.erase(r_vRocks.begin() + i);
			}
		}
	}
}

void ProjectileManager::render()
{
	if (!r_vRocks.empty())
	{
		for (int i = 0; i < (int)r_vRocks.size(); i++)
			r_vRocks[i]->render();
	}
}


ProjectileManager::~ProjectileManager()
{
}
