#pragma once
#include "LevelManager.h"

class LevelStateManager
{
private:
	LevelStateManager();
	int currentLevel;
public:
	static LevelStateManager& getInstance();
	void changeLevel(int level);
	~LevelStateManager();
};

