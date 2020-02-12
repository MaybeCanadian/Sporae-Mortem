#include "Map.h"

Map::Map()
{
	WallID = TextureManager::getInstance().addTexture("wall.png");
	//LoadMap(map);
	src = { 0,0,GRID,GRID };
	dest = { 0,0,GRID,GRID };
	setWallVec();
}
Map::~Map()
{
}
Map::Map(vector<SDL_Rect> v)
{
	wallVec = v;
}
//void Map::LoadMap(int arr[GRIDROW][GRIDCOLUMN])
//{
//	for (int row = 0; row < GRIDROW; row++)
//	{
//		for (int column = 0; column < GRIDCOLUMN; column++)
//		{
//			map[row][column] = arr[row][column];
//		}
//	}
//}
void Map::DrawMap()
{
	int type = 0;
	for (int row = 0; row < GRIDROW; row++)
	{
		for (int column = 0; column < GRIDCOLUMN; column++)
		{
			type = map[row][column];
			dest.x = column * GRID;
			dest.y = row * GRID;
			switch (type)
			{
			case 0:
			{
				TextureManager::getInstance().Draw(WallID, &dest, &src, 0, NULL, SDL_FLIP_NONE);
				break;
			}
			default:
				break;
			}
		}
	}
}
void Map::setWallVec()
{
	for (int row = 0; row < GRIDROW; row++)
	{
		for (int column = 0; column < GRIDCOLUMN; column++)
		{
			if (map[row][column] == 0)
				wallVec.push_back({ GRID * column, GRID * row, GRID, GRID });
		}
	}
}
float Map::getDistance(SDL_Rect a, SDL_Rect b)
{
	vector<int> centerA = { a.x + a.w / 2, a.y + a.h / 2 },
		centerB = { b.x + b.w / 2, b.y + b.h / 2 };
	return sqrt(pow(centerA[0] - centerB[0], 2) + pow(centerA[1] - centerB[1], 2));
}
bool Map::closer(SDL_Rect player, SDL_Rect before, SDL_Rect recent)
{
	return getDistance(player, recent) < getDistance(player, before);
}
bool Map::notHitBound(SDL_Rect player, char wsad, int speed)
{
	if (wsad == 'w' && player.y - above.y - above.h - speed <= 0)
		return false;
	if (wsad == 's' && below.y - player.y - player.h - speed <= 0)
		return false;
	if (wsad == 'a' && player.x - left.x - left.w - speed <= 0)
		return false;
	if (wsad == 'd' && right.x - player.x - player.w - speed <= 0)
		return false;
	return true;
}
void Map::setWSAD(SDL_Rect p)
{
	above = { WIDTH / 2,-GRID,GRID,GRID }, below = { WIDTH / 2,HEIGHT,GRID,GRID },
		left = { -GRID,HEIGHT / 2,GRID,GRID }, right = { WIDTH,HEIGHT / 2,GRID,GRID };
	for (int index = 0; index < wallVec.size(); index++)
	{
		SDL_Rect a = wallVec[index];
		if (abs(a.x - p.x) + abs(a.x + a.w - p.x - p.w) < a.w + p.w)
		{
			if (a.h + a.y < p.y && closer(p, above, a))
				above = a;
			if (a.y > p.h + p.y && closer(p, below, a))
				below = a;
		}
		if (abs(a.y - p.y) + abs(a.y + a.h - p.y - p.h) < a.h + p.h)
		{
			if (a.x + a.w < p.x && closer(p, left, a))
				left = a;
			if (a.x > p.x + p.w && closer(p, right, a))
				right = a;
		}
	}
}

vector<SDL_Rect> Map::getWallVec()
{
	return wallVec;
}

