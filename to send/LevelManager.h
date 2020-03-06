#pragma once
#include "engine.h"
#include <fstream>
#include "wall.h"
#include "LoadZone.h"

class LoadZone;
class wall;
class LevelManager
{
private:
	LevelManager();
	std::vector<wall*> w_vWalls;
	std::vector<LoadZone*> z_vLoad;

public:
	static LevelManager& getInstance();
	~LevelManager();
	bool initManager();
	void clean();
	void render();
	void leaveLevel();
	void loadLevel(int level);
};

