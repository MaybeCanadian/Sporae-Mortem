#include "LevelManager.h"



LevelManager::LevelManager()
{
}

LevelManager & LevelManager::getInstance()
{
	static LevelManager instance;
	return instance;
}

LevelManager::~LevelManager()
{
}

bool LevelManager::initManager()
{
	//nothing to init yet
	std::cout << "levelManager init.\n";
	return true;
}

void LevelManager::clean()
{
	w_vWalls.clear();
	w_vWalls.shrink_to_fit();
	z_vLoad.clear();
	z_vLoad.shrink_to_fit();
	std::cout << "levelManager clean.\n";
}

void LevelManager::render()
{
	if (!w_vWalls.empty())
	{
		for (int i = 0; i < (int)w_vWalls.size(); i++)
			w_vWalls[i]->render();
	}
}

void LevelManager::leaveLevel()
{
	w_vWalls.clear();
	w_vWalls.shrink_to_fit();
	z_vLoad.clear();
	z_vLoad.shrink_to_fit();
}

void LevelManager::loadLevel(int level)
{
	//it would open a file here
}
