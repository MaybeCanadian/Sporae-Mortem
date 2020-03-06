#pragma once
#include "ObjectManager.h"

class EnemyManager
{
private:
public:
	EnemyManager();
	bool initManager(); //inits the manager
	void clean(); //cleans up the manager
	~EnemyManager();
};

