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

void LevelStateManager::clean()
{
	//nothing to clean yet
}

bool LevelStateManager::initManager()
{
	//nothing to init yet
	std::cout << "levelStateManager init.\n";
	return true;
}

void LevelStateManager::changeLevel(int level)
{
	LevelManager::getInstance().leaveLevel();
	currentLevel = level;
	LevelManager::getInstance().loadLevel(level);
}

LevelStateManager::~LevelStateManager()
{
}
