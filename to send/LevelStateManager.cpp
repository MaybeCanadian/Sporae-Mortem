#include "LevelStateManager.h"



LevelStateManager::LevelStateManager()
{
	currentLevel = 0;
}


LevelStateManager & LevelStateManager::getInstance()
{
	static LevelStateManager instance;
	return instance;
}

void LevelStateManager::changeLevel(int level)
{
	currentLevel = level;
}

LevelStateManager::~LevelStateManager()
{
}
