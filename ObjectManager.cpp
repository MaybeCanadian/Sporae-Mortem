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

PickupManager * ObjectManager::getPickupManager()
{
	return Pickups;
}

LockedManager * ObjectManager::getLocked()
{
	return Locked;
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
						Pickups = new PickupManager();
						if (Pickups->initManager())
						{
							Locked = new LockedManager();
							if (Locked->initManager())
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
	Pickups->clean();
	Locked->clean();

	std::cout << "objectManager clean.\n";
}

void ObjectManager::update()
{	
	projectilemanager->update();
	playermanager->update();
	enemymanager->update();
	soundmanager->update();
	Pickups->update();
	Locked->update();
}

void ObjectManager::render()
{
	projectilemanager->render();
	soundmanager->render();
	enemymanager->render();
	playermanager->render();
	Pickups->render();
	Locked->render();
	//pathing->render(); this was for testing purposes
}

ObjectManager::~ObjectManager()
{
}
