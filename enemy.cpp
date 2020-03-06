#include "enemy.h"

enemy::enemy(int x, int y, double rotation)
{
	m_dst = { x, y, 10, 10 };
	detectRadius = 40;
	this->rotation = rotation;
	pathTarget = { m_dst.x, m_dst.y };
}

void enemy::update()
{
	if (ObjectManager::getInstance().getSoundManager()->DetectSounds(detectRadius, &m_dst, &nearest))
	{
		nearest = pathTarget;
	}

	rotation = atan2(pathTarget.y - m_dst.y, pathTarget.x - m_dst.x);
}

enemy::~enemy()
{
}
