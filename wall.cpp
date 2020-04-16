#include "wall.h"



wall::wall(int x, int y, int type, int id)
{
	w_dst = { x, y, GRID , GRID };
	w_SRC = {40 * type, 0, 40, 40 };
	TextureID = id;
}

void wall::render()
{
	if (engine::getInstance().getMode() == 0)
	{
		TextureManager::getInstance().Draw(TextureID, &w_SRC, &w_dst);
	}
	else if (engine::getInstance().getMode() == 1)
	{
		TextureManager::getInstance().Draw(0, NULL, &w_dst);
	}
}

SDL_Rect * wall::getRect()
{
	return &w_dst;
}

wall::~wall()
{
}
