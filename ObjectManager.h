#pragma once
#include "basic_includes.h"
#include "Enemy.h"
class Enemy;
class ObjectManager
{
private:
	ObjectManager();
	vector<Enemy*> EnemyVector;
	//vector<Projectile*> ProjectileVector;
public:
	static ObjectManager& getInstance();
	~ObjectManager();
};

