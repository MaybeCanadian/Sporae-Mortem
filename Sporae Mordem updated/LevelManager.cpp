#include "LevelManager.h"



LevelManager::LevelManager()
{
}

LevelManager & LevelManager::getInstance()
{
	static LevelManager instance;
	return instance;
}

LevelManager::~LevelManager()
{
}

bool LevelManager::initManager()
{
	if (LevelStateManager::getInstance().initManager())
	{
		wallID = TextureManager::getInstance().addTexture("wall.png");
		std::cout << "levelManager init.\n";
		return true;
	}
	else return false;
}

void LevelManager::addWall(int x, int y, int type)
{
	w_vWalls.push_back(new wall(x, y, type, wallID));
}

void LevelManager::addLoadZone(int x, int y, int newZone)
{
	z_vLoad.push_back(new LoadZone(x, y, newZone));
}

bool LevelManager::checkWallNear(SDL_Rect * pos)
{
	for (int i = 0; i < (int)w_vWalls.size(); i++)
	{
		if (UTIL::distanceRect(w_vWalls[i]->getRect(), pos) < 50);
		{
			if (UTIL::AABBcollide(pos, w_vWalls[i]->getRect()))
				return true;
		}
	}
	return false;
}

wall* LevelManager::getWall(int i)
{
	return w_vWalls[i];
}

int LevelManager::getWallNum()
{
	return (int)w_vWalls.size();
}

void LevelManager::clean()
{
	w_vWalls.clear();
	w_vWalls.shrink_to_fit();
	z_vLoad.clear();
	z_vLoad.shrink_to_fit();
	std::cout << "levelManager clean.\n";
}

void LevelManager::render()
{
	if (!w_vWalls.empty())
	{
		for (int i = 0; i < (int)w_vWalls.size(); i++)
			w_vWalls[i]->render();
	}
}

void LevelManager::leaveLevel()
{
	w_vWalls.clear();
	w_vWalls.shrink_to_fit();
	z_vLoad.clear();
	z_vLoad.shrink_to_fit();
	std::cout << "level cleared.\n";
}

void LevelManager::loadLevel(int level)
{
	std::ifstream file("map.txt");

	if (!file)
		std::cout << "level load error.\n";

	int gridrows, gridcols;
	std::string line;
	char input;

	file >> gridrows >> gridcols;

	if (!file.eof())
	{
		for (int row = 0; row < gridrows; row++)
		{
			file >> line;
			for (int col = 0; col < gridcols; col++)
			{
				input = line.at(col);
				
				switch (input)
				{
				case '0':
					addWall(GRID * col, GRID * row, 1);
					break;
				case '1':
					break;
				case '2':
					break;
				}
			}
		}
	}

}
