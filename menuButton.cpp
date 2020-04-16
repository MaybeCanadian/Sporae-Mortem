#include "menuButton.h"



void menuButton::onClick()
{
	ObjectManager::getInstance().getPlayerManager()->clearPlayers();
	LevelStateManager::getInstance().reset();
	StateManager::getInstance().changeState(MENU);
}

menuButton::menuButton(int x, int y, int w, int h, int id)
{
	b_dst = { x, y, w, h };
	textueID = id;
}

menuButton::~menuButton()
{
}
