#pragma once
#include "engine.h"
#include "SoundManager.h"
#include "EnemyManager.h"
#include "PlayerManager.h"
#include "ProjectileManager.h"
#include "Pathfinder.h"

class SoundManager;
class EnemyManager;
class PlayerManager;
class ProjectileManager;
class Pathfinder;
class ObjectManager
{
private:
	ObjectManager();
	SoundManager* soundmanager;
	EnemyManager* enemymanager;
	PlayerManager* playermanager;
	ProjectileManager* projectilemanager;
	Pathfinder* pathing;

public:
	static ObjectManager& getInstance();
	SoundManager* getSoundManager();
	EnemyManager* getEnemyManager();
	PlayerManager* getPlayerManager();
	ProjectileManager* getProjectileManager();
	Pathfinder* getPathFinder();
	bool initManager();
	void clean();
	void update();
	void render();
	~ObjectManager();
};

