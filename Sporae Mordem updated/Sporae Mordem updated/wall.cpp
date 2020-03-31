#include "wall.h"



wall::wall(int x, int y, int type, int id)
{
	w_dst = { x, y, GRID , GRID };
	this->type = type;
	TextureID = id;
}

void wall::render()
{
	TextureManager::getInstance().Draw(TextureID, NULL, &w_dst);
}

SDL_Rect * wall::getRect()
{
	return &w_dst;
}


wall::~wall()
{
}
