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
	onLoadZone = false;
	if (LevelStateManager::getInstance().initManager())
	{
		wallID = TextureManager::getInstance().addTexture("Image/wall.png");
		LZsound = AudioManager::getInstance().addSound("sound/door_open_sound.mp3");
		std::cout << "levelManager init.\n";
		return true;
	}
	else return false;
}

void LevelManager::addWall(int x, int y, int type)
{
	w_vWalls.push_back(new wall(x, y, type, wallID));
}

void LevelManager::addLoadZone(int x, int y, int newZone, int wall)
{
	z_vLoad.push_back(new LoadZone(x, y, newZone, wall, LZsound));
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
	leaveLevel();
	LevelStateManager::getInstance().clean();
	std::cout << "levelManager clean.\n";
}

void LevelManager::render()
{
	if (!w_vWalls.empty())
	{
		for (int i = 0; i < (int)w_vWalls.size(); i++)
		{
			w_vWalls[i]->render();
		}
	}
	if (!z_vLoad.empty())
	{
		for (int i = 0; i < (int)z_vLoad.size(); i++)
		{
			z_vLoad[i]->render();
		}
	}
}

void LevelManager::update()
{
	if (!z_vLoad.empty())
	{
		for (int i = 0; i < (int)z_vLoad.size(); i++)
		{
			z_vLoad[i]->update();
		}
	}

	if (onLoadZone == true)
	{
		onLoadZone = false;
		for (int i = 0; i < (int)z_vLoad.size(); i++)
		{
			for (int j = 0; j < ObjectManager::getInstance().getPlayerManager()->getNumPlayers(); j++)
			{
				if (UTIL::AABBcollide(z_vLoad[i]->getRect(), ObjectManager::getInstance().getPlayerManager()->getPlayers(j)->getRect()))
				{
					onLoadZone = true;
				}
			}
		}

	}
}

void LevelManager::leaveLevel()
{
	cleanWalls();
	cleanLoad();
	ObjectManager::getInstance().getPathFinder()->clearNodes();
	std::cout << "level cleared.\n";
}

void LevelManager::loadLevel(std::string level, std::string levelData, bool key, bool door, int unlocked)
{
	const char * buffer = level.c_str();
	std::ifstream file(buffer);
	buffer = levelData.c_str();
	std::fstream data(buffer);

	if (!file)
		std::cout << "level load error.\n";

	if (!data)
		std::cout << "level data load error.\n";

	int gridrows, gridcols;
	std::string line;
	char input;
	int datainput;
	int datainput2;

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
					ObjectManager::getInstance().getPathFinder()->addNode(GRID * col, GRID * row, false);
					break;
				case '1':
					ObjectManager::getInstance().getPathFinder()->addNode(GRID*col, GRID*row, true);
					break;
				case '2':
					data >> datainput;
					data >> datainput2;
					addLoadZone(GRID * col, GRID * row, datainput, datainput2);
					ObjectManager::getInstance().getPathFinder()->addNode(GRID*col, GRID*row, true);
					break;
				case '3':
				{
					ObjectManager::getInstance().getPathFinder()->addNode(GRID * col, GRID * row, false);
					if (door == true)
					{
						if(unlocked == false)
							ObjectManager::getInstance().getLocked()->addDoor(GRID * col, GRID * row, 1, 4);
					}
					else
					{
						addWall(GRID * col, GRID * row, 1);
					}
					break;
				}
				}
			}
		}
	}
	file.close();

	//tell pathfinder data
	ObjectManager::getInstance().getPathFinder()->setData(gridrows, gridcols);
	ObjectManager::getInstance().getPathFinder()->loadNeighbours();
	
	//now we load enemies

	int num, x, y, type;

	data >> num;
	for (int i = 0; i < num; i++)
	{
		data >> x >> y >> type;
		ObjectManager::getInstance().getEnemyManager()->addEnemy(x * GRID, y * GRID, type);
		std::cout << "generateing enemy at " << x << " " << y << std::endl;
	}
	
	//now we load key if we are told to
	if (key == true)
	{
		std::cout << "key should spawn.\n";
		data >> num;
		for (int i = 0; i < num; i++)
		{
			data >> x >> y >> type;
			ObjectManager::getInstance().getPickupManager()->addKey(x * GRID, y * GRID, type);
		}
	}


	data.close();
}

bool LevelManager::getOnloadZone()
{
	return onLoadZone;
}

void LevelManager::setOnloadZone(bool input)
{
	onLoadZone = input;
}

void LevelManager::cleanWalls()
{
	if (!w_vWalls.empty())
	{
		for (int i = 0; i < (int)w_vWalls.size(); i++)
		{
			delete w_vWalls[i];
			w_vWalls[i] = nullptr;
		}

		w_vWalls.clear();
		w_vWalls.shrink_to_fit();
	}
}

void LevelManager::cleanLoad()
{
	if (!z_vLoad.empty())
	{
		for (int i = 0; i < (int)z_vLoad.size(); i++)
		{
			delete z_vLoad[i];
			z_vLoad[i] = nullptr;
		}

		z_vLoad.clear();
		z_vLoad.shrink_to_fit();
	}
}
