#pragma once
#include "engine.h"
#include "SoundManager.h"
#include "EnemyManager.h"
#include "PlayerManager.h"
#include "ProjectileManager.h"
#include "Pathfinder.h"
#include "PickupManager.h"
#include "LockedManager.h"

class SoundManager;
class EnemyManager;
class PlayerManager;
class ProjectileManager;
class Pathfinder;
class PickupManager;
class LockedManager;
class ObjectManager
{
private:
	ObjectManager();
	SoundManager* soundmanager;
	EnemyManager* enemymanager;
	PlayerManager* playermanager;
	ProjectileManager* projectilemanager;
	Pathfinder* pathing;
	PickupManager* Pickups;
	LockedManager* Locked;

public:
	static ObjectManager& getInstance();
	SoundManager* getSoundManager();
	EnemyManager* getEnemyManager();
	PlayerManager* getPlayerManager();
	ProjectileManager* getProjectileManager();
	Pathfinder* getPathFinder();
	PickupManager* getPickupManager();
	LockedManager* getLocked();
	bool initManager();
	void clean();
	void update();
	void render();
	~ObjectManager();
};

