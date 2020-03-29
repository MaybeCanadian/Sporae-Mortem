#pragma once
#include "LevelManager.h"

class LevelStateManager
{
private:
	int currentLevel;
	std::string levels[4];
	std::string levelsdata[4];

private:
	LevelStateManager();
public:
	static LevelStateManager& getInstance();
	void clean();
	bool initManager();
	void changeLevel(int level);
	~LevelStateManager();
};

