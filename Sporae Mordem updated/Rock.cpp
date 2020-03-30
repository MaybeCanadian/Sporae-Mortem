#include "Rock.h"

Rock::Rock(int x, int y, double rot, int s1, int s2)
{
	pos = { x, y, 5, 5};
	rotation = rot;
	speed = 5;
	r_active = true;
	soundthrow = s1;
	soundhit = s2;
	AudioManager::getInstance().playSound(soundthrow, -1, 0);
}

void Rock::update()
{
	pos.x = pos.x + (speed * cos(rotation));
	pos.y = pos.y + (speed * sin(rotation));

	if (pos.x < 0 || pos.y < 0 || pos.x > WIDTH || pos.y > HEIGHT || LevelManager::getInstance().checkWallNear(&pos))
	{
		r_active = false;
		ObjectManager::getInstance().getSoundManager()->soundsCreate(pos.x, pos.y, 50, 10);
		AudioManager::getInstance().playSound(soundhit, -1, 0);
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
