#pragma once
#include "LevelManager.h"

class LevelStateManager
{
private:
	int currentLevel;
	int currentZone;
	std::string levels[5];
	std::string levelsdata[5];
	bool haskey[4];
	bool hasdoor[4];
	bool unlocked;
private:
	LevelStateManager();
public:
	static LevelStateManager& getInstance();
	void clean();
	bool initManager();
	void changeLevel(int level);
	void setHasKeyCurrent(bool input);
	void setUnlocked(bool input);
	~LevelStateManager();
};

