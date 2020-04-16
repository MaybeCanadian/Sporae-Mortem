#pragma once
#include "ObjectManager.h"
#include "enemy.h"

class enemy;
class EnemyManager
{
private:
	std::vector<enemy*> e_vEnemies;
	int EnemyID;
	int enemysound;

private:
	void loadTextures();

public:
	EnemyManager();
	bool initManager(); //inits the manager
	void clean(); //cleans up the manager
	void addEnemy(int x, int y, int type);
	void update();
	void render();
	void ClearEnemies();
	~EnemyManager();
};

