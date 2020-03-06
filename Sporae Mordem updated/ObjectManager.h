#pragma once
#include "engine.h"
#include "SoundManager.h"
#include "EnemyManager.h"
#include "PlayerManager.h"
#include "ProjectileManager.h"

class SoundManager;
class EnemyManager;
class PlayerManager;
class ProjectileManager;
class ObjectManager
{
private:
	ObjectManager();
	SoundManager* soundmanager;
	EnemyManager* enemymanager;
	PlayerManager* playermanager;
	ProjectileManager* projectilemanager;

public:
	static ObjectManager& getInstance();
	SoundManager* getSoundManager();
	EnemyManager* getEnemyManager();
	PlayerManager* getPlayerManager();
	ProjectileManager* getProjectileManager();
	bool initManager();
	void clean();
	void update();
	void render();
	~ObjectManager();
};

