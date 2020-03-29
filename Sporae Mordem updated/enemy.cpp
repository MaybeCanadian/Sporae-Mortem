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
	if (ObjectManager::getInstance().getSoundManager()->DetectSounds(detectRadius, &m_dst, nearSound))
	{
		pathTarget = *nearSound;
		return true;
	}
	else return false;
}

enemy::enemy(int x, int y, int type, int id)
{
	m_dst = { x, y, 30, 30 };
	detectRadius = 40;
	lookRange = 100;
	pathTarget = { m_dst.x, m_dst.y };
	textureID = id;
	this->type = type;
}

void enemy::update()
{
	if (listen(&nearSound))
	{
		std::cout << "heard sound.\n";
	}
	if (look(&nearPlayer))
	{
		std::cout << "saw player.\n";
	}
}

void enemy::render()
{
	TextureManager::getInstance().Draw(textureID, NULL, &m_dst);
}

enemy::~enemy()
{
}
