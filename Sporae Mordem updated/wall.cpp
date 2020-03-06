#include "wall.h"



wall::wall(int x, int y, int type)
{
}

void wall::render()
{
	TextureManager::getInstance().SetDrawColor(255, 255, 255, 255);
	TextureManager::getInstance().FillRect(&w_dst);
}


wall::~wall()
{
}
