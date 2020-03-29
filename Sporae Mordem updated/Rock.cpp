#include "Rock.h"

Rock::Rock(int x, int y, double rot)
{
	pos = { x, y, 5, 5};
	rotation = rot;
	speed = 5;
	r_active = true;
}

void Rock::update()
{
	pos.x = pos.x + (speed * cos(rotation));
	pos.y = pos.y + (speed * sin(rotation));

	if (pos.x < 0 || pos.y < 0 || pos.x > WIDTH || pos.y > HEIGHT || LevelManager::getInstance().checkWallNear(&pos))
	{
		r_active = false;
		ObjectManager::getInstance().getSoundManager()->soundsCreate(pos.x, pos.y, 50, 10);
		std::cout << "noise\n";
	}
}

bool Rock::getActive()
{
	return r_active;
}

void Rock::render()
{
	TextureManager::getInstance().SetDrawColor(0, 0, 0, 255);
	TextureManager::getInstance().FillRect(&pos);
}

Rock::~Rock()
{
}
