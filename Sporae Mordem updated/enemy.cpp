#include "enemy.h"

bool enemy::look(SDL_Point * nearPlayer)
{
	for (int i = 0; i < ObjectManager::getInstance().getPlayerManager()->getNumPlayers(); i++)
	{
		if (UTIL::distanceRect(ObjectManager::getInstance().getPlayerManager()->getPlayers(i)->getRect(), &m_dst) < lookRange)
		{
			SDL_Point buffer1 = { ObjectManager::getInstance().getPlayerManager()->getPlayers(i)->getRect()->x, ObjectManager::getInstance().getPlayerManager()->getPlayers(i)->getRect()->y };
			SDL_Point buffer2 = { m_dst.x, m_dst.y };
			int rot = UTIL::Rotation(&buffer1, &buffer2);

			int lookbound1 = rotation + 30; 
			int lookbound2 = rotation - 30;
			if (lookbound1 > 360)
				lookbound1 = lookbound1 - 360;
			if (lookbound2 < 0)
				lookbound2 = lookbound2 + 360;

			if (!(rot > lookbound1 || rot < lookbound2))
			{
				nearPlayer->x = buffer1.x;
				nearPlayer->y = buffer2.y;
				return true;
			}
		}
	}
	return false;
}

bool enemy::listen(SDL_Point * nearSound)
{
	if (ObjectManager::getInstance().getSoundManager()->DetectSounds(&m_dst, nearSound))
	{
		return true;
	}
	else return false;
}

enemy::enemy(int x, int y, int type, int id)
{
	m_dst = { x, y, 30, 30 };
	lookRange = 100;
	textureID = id;
	this->type = type;
	speed = 5;
	pathtarget = nullptr;
	moving = false;
	target = false;
	rotation = 90;
}

void enemy::update()
{
	if (listen(&nearSound)) //then we listen
	{
		clearpath();

		if (ObjectManager::getInstance().getPathFinder()->findPath(&path, m_dst.x, m_dst.y, nearSound.x, nearSound.y))
		{
			target = true;
			std::cout << "path size is " << path.size() << std::endl;
		}
		else
			target = false;
	}
	if (look(&nearPlayer))
	{
		std::cout << "see Player.\n";
	}
	if (target)
	{
		followpath();
	}
}

void enemy::render()
{
	TextureManager::getInstance().DrawEx(textureID, &m_dst, NULL, rotation - 90, NULL, SDL_FLIP_NONE);
}

void enemy::clearpath()
{
		path.clear();
		path.shrink_to_fit();
		pathtarget = nullptr;
		std::cout << "path cleared.\n";
}

bool enemy::followpath()
{
	if (pathtarget == nullptr)
	{
		if (!path.empty())
		{
			pathtarget = &path[0];
		}
		else
		{
			target = false;
			return false;
		}

	}
	else
	{
		moving = move(pathtarget);
	}
}

bool enemy::move(SDL_Point* pos)
{
	bool up = false, down = false, left = false, right = false;
	SDL_Point buffer = { m_dst.x, m_dst.y };
	if (m_dst.x < pos->x)
	{
		left = true;
		if (UTIL::distancePoint(&buffer, pathtarget) > 2)
			m_dst.x = m_dst.x + speed;
		else
			m_dst.x = m_dst.x + 1;
	}
	else if (m_dst.x > pos->x)
	{
		right = true;
		if (UTIL::distancePoint(&buffer, pathtarget) > 2)
			m_dst.x = m_dst.x - speed;
		else
			m_dst.x = m_dst.x - 1;
	}

	if (m_dst.y < pos->y)
	{
		down = true;
		if (UTIL::distancePoint(&buffer, pathtarget) > 2)
			m_dst.y = m_dst.y + speed;
		else
			m_dst.y = m_dst.y + 1;
	}
	else if (m_dst.y > pos->y)
	{
		up = true;
		if (UTIL::distancePoint(&buffer, pathtarget) > 2)
			m_dst.y = m_dst.y - speed;
		else
			m_dst.y = m_dst.y - 1;
	}
	
	if (up)
		if (right)
			rotation = 45;
		else if (left)
			rotation = 135;
		else
			rotation = 90;
	else if (down)
		if (right)
			rotation = 315;
		else if (left)
			rotation = 225;
		else
			rotation = 270;
	else if (right)
		rotation = 0;
	else if (left)
		rotation = 180;
	

	if (m_dst.x == pos->x && m_dst.y == pos->y)
	{
		std::cout << "reached a target.\n";
		pathtarget = nullptr;
		path.erase(path.begin());
		return false;
	}
	else
		return true;
}

enemy::~enemy()
{
}
