#include "Rock.h"

Rock::Rock(int x, int y, double rot, int s1, int s2, int t1)
{
	pos = { x, y, 5, 5};
	future = { 0, 0, 5, 5 };
	rotation = rot;
	speed = 5;
	r_active = true;
	soundthrow = s1;
	soundhit = s2;
	AudioManager::getInstance().playSound(soundthrow, -1, 0);
	texture = t1;
}

void Rock::update()
{
	future.x = pos.x;
	future.y = pos.y;
	future.x = future.x + (speed * cos(rotation));
	future.y = future.y + (speed * sin(rotation));

	if (future.x < 0 || future.y < 0 || future.x > WIDTH || future.y > HEIGHT || LevelManager::getInstance().checkWallNear(&future))
	{
		r_active = false;
		ObjectManager::getInstance().getSoundManager()->soundsCreate(pos.x, pos.y, 300, 0);
		AudioManager::getInstance().playSound(soundhit, -1, 0);
		std::cout << "noise\n";
	}
	else
	{
		pos.x = pos.x + (speed * cos(rotation));
		pos.y = pos.y + (speed * sin(rotation));
	}

}

bool Rock::getActive()
{
	return r_active;
}

void Rock::render()
{
	if (engine::getInstance().getMode() == 0)
	{
		TextureManager::getInstance().Draw(texture, NULL, &pos);
	}
	else if(engine::getInstance().getMode() == 1)
	{
		TextureManager::getInstance().Draw(0, NULL, &pos);
	}
}

Rock::~Rock()
{
}
