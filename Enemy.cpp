#include "Enemy.h"

Enemy::Enemy(vector<SDL_Rect> v)
{
	m_dst = {19*GRID,9*GRID,ENEMYSIZE,ENEMYSIZE};
	wallVec = v;
	rotation = 90;
	srand(time(NULL));
	soundDetectRadius = 200;
}

Enemy::~Enemy()
{
}

double const Enemy::getSoundRadius()
{
	return soundDetectRadius;
}

void Enemy::update()
{
	if (!SoundManager::getInstance().getSoundVector().empty())
	{
		for (int i = 0; i < (int)SoundManager::getInstance().getSoundVector().size(); i++)
		{
			if (SoundManager::getInstance().soundDetect(soundDetectRadius, m_dst, *(SoundManager::getInstance().getSoundVector()[i])))
				cout << "sound detected" << endl;
		}
	}
	if (!(check('w')) && rotation == 0)
		(rand()%2 == 0)?turnRight():turnLeft();
	else if (!(check('s')) && rotation == 180)
		(rand() % 2 == 0) ? turnRight() : turnLeft();
	else if(!(check('a')) && rotation == 270)
		(rand() % 2 == 0) ? turnRight() : turnLeft();
	else if(!(check('d')) && rotation == 90)
		(rand() % 2 == 0) ? turnRight() : turnLeft();
	else
		move();
}

void Enemy::render()
{

}

SDL_Rect const Enemy::getRect()
{
	return m_dst;
}

double const Enemy::getRotation()
{
	return rotation;
}

void Enemy::turnRight()
{
	rotation += 90;
	if (rotation == 360)
		rotation = 0;
}

void Enemy::turnLeft()
{
	if (rotation == 0)
		rotation = 360;
	rotation -= 90;
}

bool Enemy::check(char wsad)
{
	Map map(wallVec);
	map.setWSAD(m_dst);
	return map.notHitBound(m_dst, wsad, ENEMYSPEED);
}

void Enemy::move()
{
	if ((rotation == 0 || rotation == 360) && m_dst.y > 0 && check('w'))
	{
		m_dst.y -= ENEMYSPEED;
	}
	if (rotation == 180 && m_dst.y < HEIGHT - m_dst.h && check('s'))
	{
		m_dst.y += ENEMYSPEED;
	}
	if (rotation == 270 && m_dst.x > 0 && check('a'))
	{
		m_dst.x -= ENEMYSPEED;
	}
	if (rotation == 90 && m_dst.x - m_dst.w < WIDTH && check('d'))
	{
		m_dst.x += ENEMYSPEED;
	}
}
