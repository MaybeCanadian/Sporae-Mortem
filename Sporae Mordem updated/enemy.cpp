#include "enemy.h"

bool enemy::look(SDL_Point * nearPlayer)
{
	SDL_Point Startbuffer = { m_dst.x + m_dst.w / 2, m_dst.y + m_dst.h / 2 };
	double rot = rotation * 180 / 3.14;
	double neardistance = 100000;
	bool see = false;
	double arcs[18];
	for (int i = 0; i < 18; i++)
	{
		arcs[i] = rot - 45 + 5 * i;
		if (arcs[i] < 0)
		{
			arcs[i] = 360 + arcs[i];
		}
		else if (arcs[i] >= 360)
		{
			arcs[i] = arcs[i] - 360;
		}

		arcs[i] = arcs[i] * 3.14 / 180;
	}

	for (int i = 0; i < ObjectManager::getInstance().getPlayerManager()->getNumPlayers(); i++)
	{
		for (int j = 0; j < 18; j++)
		{
			SDL_Point endBuffer = { Startbuffer.x + lookRange * cos(arcs[j]), Startbuffer.y + lookRange * cos(arcs[j]) };
			SDL_Point rectStart = { ObjectManager::getInstance().getPlayerManager()->getPlayers(i)->getRect()->x,  ObjectManager::getInstance().getPlayerManager()->getPlayers(i)->getRect()->y };
			if (UTIL::lineRectCheck(Startbuffer, endBuffer, rectStart, ObjectManager::getInstance().getPlayerManager()->getPlayers(i)->getRect()->w, ObjectManager::getInstance().getPlayerManager()->getPlayers(i)->getRect()->h))
			{
				bool blocked = false;
				//at this point weve seen a playing, now we see if there is an interescting wall that is closer
				double distance = UTIL::distancePoint(&Startbuffer, &rectStart);
				for (int k = 0; k < (int)LevelManager::getInstance().getWallNum(); k++)
				{
					SDL_Point wallBuffer = { LevelManager::getInstance().getWall(k)->getRect()->x + LevelManager::getInstance().getWall(k)->getRect()->w,
						LevelManager::getInstance().getWall(k)->getRect()->y + LevelManager::getInstance().getWall(k)->getRect()->h };

					double walldist = UTIL::distancePoint(&Startbuffer, &wallBuffer);
					if (walldist < distance)
					{
						SDL_Point wallstartbuffer = { LevelManager::getInstance().getWall(k)->getRect()->x, LevelManager::getInstance().getWall(k)->getRect()->y };
						if (UTIL::lineRectCheck(Startbuffer, endBuffer, wallstartbuffer, LevelManager::getInstance().getWall(k)->getRect()->w, LevelManager::getInstance().getWall(k)->getRect()->h))
						{
							blocked = true;
						}
					}
				}

				//afte checking all walls
				if (blocked == false)
				{
					//seen player
					if (distance < neardistance)
					{
						*nearPlayer = { ObjectManager::getInstance().getPlayerManager()->getPlayers(i)->getRect()->x, ObjectManager::getInstance().getPlayerManager()->getPlayers(i)->getRect()->y };
						if (see == false)
							see = true;
					}
				}
			}
		}
	}

	return see;
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
