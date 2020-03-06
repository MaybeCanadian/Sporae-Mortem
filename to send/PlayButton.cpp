#include "PlayButton.h"



void PlayButton::onClick()
{
	StateManager::getInstance().changeState(GAME);
}

PlayButton::PlayButton(int x, int y, int w, int h, int id)
{
	b_dst = { x, y, w, h };
	textueID = id;
}

PlayButton::~PlayButton()
{
}
