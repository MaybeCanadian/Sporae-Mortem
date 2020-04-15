#include "pauseButton.h"



void pauseButton::onClick()
{
	StateManager::getInstance().changeState(PAUSE);
}

pauseButton::pauseButton(int x, int y, int w, int h, int id)
{
	b_dst = { x, y, w, h };
	textueID = id;
}


pauseButton::~pauseButton()
{
}
