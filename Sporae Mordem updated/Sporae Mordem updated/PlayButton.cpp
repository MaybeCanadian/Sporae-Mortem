#include "PlayButton.h"



void PlayButton::onClick()
{
	StateManager::getInstance().changeState(GAME);
}

PlayButton::PlayButton(int x, int y, int w, int h, int id)
{
	b_dst = { x, y, w, h };
	textueID = id;
	std::cout << "making button with texture id " << textueID << std::endl;
}

PlayButton::~PlayButton()
{
}
