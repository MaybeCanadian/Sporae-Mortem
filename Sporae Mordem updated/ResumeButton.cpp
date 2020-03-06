#include "ResumeButton.h"



void ResumeButton::onClick()
{
	StateManager::getInstance().changeState(GAME);
}

ResumeButton::ResumeButton(int x, int y, int w, int h, int id)
{
	b_dst = { x, y, w, h };
	textueID = id;
}


ResumeButton::~ResumeButton()
{
}
