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
	levels[0] = "map/lvl1.txt";
	levels[1] = "map/lvl2.txt";
	levels[2] = "map/lvl3.txt";
	levels[3] = "map/lvl4.txt";

	levelsdata[0] = "map/lvl1data.txt";
	levelsdata[1] = "map/lvl2data.txt";
	levelsdata[2] = "map/lvl3data.txt";
	levelsdata[3] = "map/lvl4data.txt";

	std::cout << "levelStateManager init.\n";
	return true;
}

void LevelStateManager::changeLevel(int level)
{
	LevelManager::getInstance().leaveLevel();
	currentLevel = level;
	LevelManager::getInstance().loadLevel(levels[level], levelsdata[level]);
}

LevelStateManager::~LevelStateManager()
{
}
