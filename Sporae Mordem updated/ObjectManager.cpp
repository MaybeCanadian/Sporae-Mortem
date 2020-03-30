#include "ObjectManager.h"



ObjectManager::ObjectManager()
{
}


ObjectManager & ObjectManager::getInstance()
{
	static ObjectManager instance;
	return instance;
}

SoundManager * ObjectManager::getSoundManager()
{
	return soundmanager;
}

EnemyManager * ObjectManager::getEnemyManager()
{
	return enemymanager;
}

PlayerManager * ObjectManager::getPlayerManager()
{
	return playermanager;
}

ProjectileManager * ObjectManager::getProjectileManager()
{
	return projectilemanager;
}

Pathfinder * ObjectManager::getPathFinder()
{
	return pathing;
}

bool ObjectManager::initManager()
{
	std::cout << "objectManager init.\n";
	soundmanager = new SoundManager();
	if (soundmanager->initManager())
	{
		enemymanager = new EnemyManager();
		if (enemymanager->initManager())
		{
			playermanager = new PlayerManager();
			if (playermanager->initManager())
			{
				projectilemanager = new ProjectileManager();
				if (projectilemanager->initManager())
				{
					pathing = new Pathfinder();
					if (pathing->initManager())
					{
						return true;
					}
					else return false;
				}
				else return false;
			}
			else return false;
		}
		else return false;
	}
	else return false;
}

void ObjectManager::clean()
{
	soundmanager->clean();
	enemymanager->clean();
	playermanager->clean();
	projectilemanager->clean();
	pathing->clean();

	std::cout << "objectManager clean.\n";
}

void ObjectManager::update()
{	
	playermanager->update();
	enemymanager->update();
	soundmanager->update();
	projectilemanager->update();
}

void ObjectManager::render()
{
	projectilemanager->render();
	soundmanager->render();
	enemymanager->render();
	playermanager->render();
	//pathing->render();
}

ObjectManager::~ObjectManager()
{
}
