#include "ExitButton.h"



void ExitButton::onClick()
{
	engine::getInstance().quit();
}

ExitButton::ExitButton(int x, int y, int w, int h, int id)
{
	b_dst = { x, y, w, h };
	textueID = id;
}

ExitButton::~ExitButton()
{
}
