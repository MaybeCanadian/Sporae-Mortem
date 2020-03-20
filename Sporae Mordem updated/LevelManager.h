#pragma once
#include "engine.h"
#include <fstream>
#include "wall.h"
#include "LoadZone.h"
#include "LevelStateManager.h"

#define GRID 40

class LoadZone;
class wall;
class LevelStateManager;
class LevelManager
{
private:
	LevelManager();
	std::vector<wall*> w_vWalls;
	std::vector<LoadZone*> z_vLoad;
	int wallID;

public:
	static LevelManager& getInstance();
	~LevelManager();
	bool initManager();
	void addWall(int x, int y, int type);
	void addLoadZone(int x, int y, int newZone);
	bool checkWallNear(SDL_Rect* pos);
	wall* getWall(int i);
	int getWallNum();
	void clean();
	void render();
	void leaveLevel();
	void loadLevel(int level);
};

