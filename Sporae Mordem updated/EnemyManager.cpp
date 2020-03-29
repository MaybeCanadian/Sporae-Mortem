#include "EnemyManager.h"



void EnemyManager::loadTextures()
{
	EnemyID = TextureManager::getInstance().addTexture("zombie.png");
}

EnemyManager::EnemyManager()
{
}

bool EnemyManager::initManager()
{
	//nothing to init yet
	loadTextures();
	std::cout << "enemyManager init.\n";
	return true;
}

void EnemyManager::clean()
{
	if (!e_vEnemies.empty())
	{
		for (int i = 0; i < (int)e_vEnemies.size(); i++)
		{
			delete &e_vEnemies[i];
			e_vEnemies[i] = nullptr;
		}
	}
	//nothing to clean yet
	std::cout << "enemyManager clean.\n";
}

void EnemyManager::addEnemy(int x, int y, int type)
{
	e_vEnemies.push_back(new enemy(x, y, type, EnemyID));
}

void EnemyManager::update()
{
	if (!e_vEnemies.empty())
	{
		for (int i = 0; i < (int)e_vEnemies.size(); i++)
		{
			e_vEnemies[i]->update();
		}
	}
}


void EnemyManager::render()
{
	if (!e_vEnemies.empty())
	{
		for(int i = 0; i < (int)e_vEnemies.size(); i++)
			e_vEnemies[i]->render();
	}
}

EnemyManager::~EnemyManager()
{
}
