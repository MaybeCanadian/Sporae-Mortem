#include "ProjectileManager.h"



ProjectileManager::ProjectileManager()
{
}

bool ProjectileManager::initManager()
{
	std::cout << "projectileManager init.\n";
	rocksound1 = AudioManager::getInstance().addSound("sound/catch.mp3");
	rocksound2 = AudioManager::getInstance().addSound("sound/stone.mp3");
	rockTexture = TextureManager::getInstance().addTexture("Image/rock.png");
	return true;
}

void ProjectileManager::clean()
{
	clearProjectiles();
	std::cout << "pojectileManager clean.\n";
}

void ProjectileManager::addRock(int x, int y, double rotation)
{
	r_vRocks.push_back(new Rock(x, y, rotation, rocksound1, rocksound2, rockTexture));
}

void ProjectileManager::update()
{
	for (int i = 0; i < (int)r_vRocks.size(); i++)
	{
		r_vRocks[i]->update();
	}
	
	if(!r_vRocks.empty())
	{
		for (int i = 0; i < (int)r_vRocks.size(); i++)
		{
			if (r_vRocks[i]->getActive() == false)
			{
				delete r_vRocks[i];
				r_vRocks[i] = nullptr;
			}
		}
		
		r_vRocks.erase(std::remove(r_vRocks.begin(), r_vRocks.end(), nullptr), r_vRocks.end());
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

void ProjectileManager::clearProjectiles()
{
	if (!r_vRocks.empty())
	{
		for (int i = 0; i < (int)r_vRocks.size(); i++)
		{
			delete r_vRocks[i];
			r_vRocks[i] = nullptr;
		}
		r_vRocks.clear();
		r_vRocks.shrink_to_fit();
	}
}


ProjectileManager::~ProjectileManager()
{
}
