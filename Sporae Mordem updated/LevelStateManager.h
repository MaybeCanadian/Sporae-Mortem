#pragma once
#include "LevelManager.h"

class LevelStateManager
{
private:
	LevelStateManager();
	int currentLevel;
public:
	static LevelStateManager& getInstance();
	void clean();
	bool initManager();
	void changeLevel(int level);
	~LevelStateManager();
};

