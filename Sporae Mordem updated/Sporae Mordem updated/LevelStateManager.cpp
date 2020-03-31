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
	std::cout << "LevelStateManager cleaned.\n";
}

bool LevelStateManager::initManager()
{ 
	//load map names
	levels[0] = "map/lvl1.txt";
	levels[1] = "map/lvl2.txt";
	levels[2] = "map/lvl3.txt";
	levels[3] = "map/lvl4.txt";
	levels[4] = "map/lvl5.txt";
	//load map data names
	levelsdata[0] = "map/lvl1data.txt";
	levelsdata[1] = "map/lvl2data.txt";
	levelsdata[2] = "map/lvl3data.txt";
	levelsdata[3] = "map/lvl4data.txt";
	levelsdata[4] = "map/lvl5data.txt";
	srand(time(NULL));

	int random = rand();
	int keyroom = rand() % 3 + 1;
	std::cout << "the key shoudl be in room " << keyroom << std::endl;
	for (int i = 0; i < 4; i++)
	{
		if (i == keyroom)
			haskey[i] = true;
		else
			haskey[i] = false;
	}
	srand(random);
	random = rand();
	int doorroom = random % 4;
	std::cout << "door should be in room " << doorroom << std::endl;

	for (int i = 0; i < 4; i++)
	{
		if (i == doorroom)
			hasdoor[i] = true;
		else
			hasdoor[i] = false;
	}

	unlocked = false;
	currentLevel = 0;

	std::cout << "levelStateManager init.\n";
	return true;
}

void LevelStateManager::changeLevel(int level)
{
	LevelManager::getInstance().leaveLevel();
	ObjectManager::getInstance().getEnemyManager()->ClearEnemies();
	ObjectManager::getInstance().getLocked()->clearDoors();
	ObjectManager::getInstance().getSoundManager()->clearSounds();
	currentLevel = level;
	LevelManager::getInstance().loadLevel(levels[level], levelsdata[level], haskey[level], hasdoor[level], unlocked);
	if(level!=0)
		LabelManager::getInstance().setActive(false);
}

void LevelStateManager::setHasKeyCurrent(bool input)
{
	haskey[currentLevel] = input;
}

void LevelStateManager::setUnlocked(bool input)
{
	unlocked = input;
}

LevelStateManager::~LevelStateManager()
{
}
