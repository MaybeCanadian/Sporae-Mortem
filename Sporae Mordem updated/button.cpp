#include "button.h"

void button::setTexture(int id)
{
	textueID = id;
}

void button::update()
{
	switch (b_state)
	{
	case STATE_UP:
	{
		if (UTIL::PointRectCollide(InputManager::getInstance().getMouse(), &b_dst))
			b_state = STATE_OVER;
		break;
	}
	case STATE_DOWN:
	{
		if (!InputManager::getInstance().getMouseState(0))
		{
			b_state = STATE_OVER;
		}
		if (!UTIL::PointRectCollide(InputManager::getInstance().getMouse(), &b_dst))
		{
			b_state = STATE_UP;
		}
		break;
	}
	case STATE_OVER:
	{
		if (!UTIL::PointRectCollide(InputManager::getInstance().getMouse(), &b_dst))
			b_state = STATE_UP;
		else if (InputManager::getInstance().getMouseClick(0))
		{
			b_state = STATE_DOWN;
			onClick();
		}
		break;
	}
	}
}

void button::render()
{
	/*b_src.x = b_src.w * (int)b_state; need to add the files
	TextureManager::getInstance().Draw(textueID, &b_src, &b_dst); */
	TextureManager::getInstance().SetDrawColor(0, 0, 0, 255);
	TextureManager::getInstance().FillRect(&b_dst);
}

button::button()
{
	b_state = STATE_UP;
}


button::~button()
{
}
