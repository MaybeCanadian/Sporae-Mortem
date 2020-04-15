#include "settingsbutton.h"



void settingsbutton::onClick()
{
	StateManager::getInstance().changeState(SETTINGS);
}

settingsbutton::settingsbutton(int x, int y, int w, int h, int id)
{
	b_dst = { x, y, w, h };
	textueID = id;
}

settingsbutton::~settingsbutton()
{
}
