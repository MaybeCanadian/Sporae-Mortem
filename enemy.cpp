#include "enemy.h"

bool enemy::look(SDL_Point * nearPlayer)
{
	if (rotation > 360)
	{
		rotation = rotation - 360;
	}
	else if (rotation < 0)
	{
		rotation = rotation + 360;
	}
	double neardist = 1000;
	for (int i = 0; i < ObjectManager::getInstance().getPlayerManager()->getNumPlayers(); i++)
	{
		double bufferRadius = ObjectManager::getInstance().getPlayerManager()->getPlayers(i)->getDetctRange();
		SDL_Point bufferPoint = { ObjectManager::getInstance().getPlayerManager()->getPlayers(i)->getRect()->x + ObjectManager::getInstance().getPlayerManager()->getPlayers(i)->getRect()->w / 2,
			ObjectManager::getInstance().getPlayerManager()->getPlayers(i)->getRect()->y - ObjectManager::getInstance().getPlayerManager()->getPlayers(i)->getRect()->h / 2 };
		SDL_Point bufferEnemy = { m_dst.x + m_dst.w /2, m_dst.y - m_dst.h / 2 };
		if (UTIL::CircleCollide(&bufferEnemy, m_dst.w, &bufferPoint, bufferRadius))
		{
			int deltaX = m_dst.x - bufferPoint.x;
			int deltaY = m_dst.y - bufferPoint.y;

			angle = atan2(deltaY, deltaX);
			angle = angle * 180 / 3.14;

			if (angle < 0)
			{
				angle = angle + 360;
			}
			else if (angle > 360)
			{
				angle = angle - 360;
			}

			int maxangle = rotation + 45;
			if (maxangle > 360)
				maxangle = maxangle - 360;
			int minangle = rotation - 45;
			if (minangle < 0)
				minangle = minangle + 360;
			
			if (maxangle > minangle)
			{
				if (angle > minangle && angle < maxangle)
				{
					if (checkwalls(&bufferPoint) == false)
					{
						int dist = sqrt(pow(bufferEnemy.x - bufferPoint.x, 2) + pow(bufferEnemy.y - bufferPoint.y, 2));
						if (dist < neardist)
						{
							neardist = dist;
							nearPlayer->x = ObjectManager::getInstance().getPlayerManager()->getPlayers(i)->getRect()->x + ObjectManager::getInstance().getPlayerManager()->getPlayers(i)->getRect()->w / 2;
							nearPlayer->y = ObjectManager::getInstance().getPlayerManager()->getPlayers(i)->getRect()->y + ObjectManager::getInstance().getPlayerManager()->getPlayers(i)->getRect()->h / 2;
						}
					}
				}
			}
			else if (maxangle < minangle)
			{
				if (!(angle < minangle && angle > maxangle))
				{
					int dist = sqrt(pow(bufferEnemy.x - bufferPoint.x, 2) + pow(bufferEnemy.y - bufferPoint.y, 2));
					if (dist < neardist)
					{
						neardist = dist;
						nearPlayer->x = ObjectManager::getInstance().getPlayerManager()->getPlayers(i)->getRect()->x + ObjectManager::getInstance().getPlayerManager()->getPlayers(i)->getRect()->w / 2;
						nearPlayer->y = ObjectManager::getInstance().getPlayerManager()->getPlayers(i)->getRect()->y + ObjectManager::getInstance().getPlayerManager()->getPlayers(i)->getRect()->h / 2;
					}
				}
			}
		}

		if (neardist < 1000)
			return true;
		return false;
	}
}

bool enemy::listen(SDL_Point * nearSound)
{
	if (ObjectManager::getInstance().getSoundManager()->DetectSounds(&m_dst, nearSound))
	{
		return true;
	}
	else return false;
}

bool enemy::checkwalls(SDL_Point* player)
{
	SDL_Point buffer;
	SDL_Point bufferEnem = { m_dst.x + m_dst.w / 2 , m_dst.y + m_dst.h / 2 };
	int deltaX = bufferEnem.x - player->x;
	int deltaY = bufferEnem.y - player->y;
	float distance = sqrt(pow(deltaX, 2) + pow(deltaY, 2));
	for (int i = 0; i < LevelManager::getInstance().getWallNum(); i++)
	{
		buffer = { LevelManager::getInstance().getWall(i)->getRect()->x + LevelManager::getInstance().getWall(i)->getRect()->w / 2,
			LevelManager::getInstance().getWall(i)->getRect()->y + LevelManager::getInstance().getWall(i)->getRect()->h / 2 };


		float dot = (((buffer.x - bufferEnem.x) * (player->x - bufferEnem.x)) + ((buffer.y - bufferEnem.y) * (player->y - bufferEnem.y))) / pow(distance, 2);

		SDL_Point closest = { bufferEnem.x + (dot * (player->x - bufferEnem.x)), bufferEnem.y + (dot * (player->y - bufferEnem.y)) };
		//check if on line
		if ((UTIL::linePointColide(&closest, &bufferEnem, player, 2)))
		{
			int actdistX = closest.x - buffer.x;
			int actdistY = closest.y - buffer.y;

			int displace = sqrt(pow(actdistX, 2) + pow(actdistY, 2));

			if (displace < LevelManager::getInstance().getWall(i)->getRect()->w)
			{
				return true;
			}
		}
	}
	return false;
}

enemy::enemy(int x, int y, int type, int id, int sound)
{
	m_dst = { x, y, 30, 30 };
	lookRange = 300;
	textureID = id;
	this->type = type;
	speed = 4;
	pathtarget.x = m_dst.x;
	pathtarget.y = m_dst.y;
	rotation = 90 * type;
	MaxVelocity = 4;
	MaxForce = 2;
	state = wander;
	wandergoal = 0;
	wanderplace = 0;
	wandertimer = 0;
	soundid = sound;
}

void enemy::update()
{
	AI();
	for (int i = 0; i < (int)ObjectManager::getInstance().getPlayerManager()->getNumPlayers(); i++)
	{
		if (UTIL::AABBcollide(&m_dst, ObjectManager::getInstance().getPlayerManager()->getPlayers(i)->getRect()))
		{
			std::cout << "player killed.\n";
			StateManager::getInstance().changeState(LOSE);
		}
	}
}

void enemy::render()
{
	if (engine::getInstance().getMode() == 0)
	{
		TextureManager::getInstance().DrawEx(textureID, &m_dst, NULL, rotation - 90, NULL, SDL_FLIP_NONE);
	}
	else if (engine::getInstance().getMode() == 1)
	{
		TextureManager::getInstance().DrawEx(0, &m_dst, NULL, rotation - 90, NULL, SDL_FLIP_NONE);
	}
}

void enemy::clearpath()
{
		path.clear();
		path.shrink_to_fit();
		pathtarget.x = m_dst.x;
		pathtarget.y = m_dst.y;
		std::cout << "path cleared.\n";
}

bool enemy::followpath()
{
	path.shrink_to_fit();
	if(!path.empty())
	{
		pathtarget = path[0];
		move(&pathtarget);

		if (m_dst.x == pathtarget.x && m_dst.y == pathtarget.y)
		{
			path.erase(path.begin());
			return true;
		}
	}
	return false;
}

void enemy::seek(SDL_Point * target)
{
	desiredVelocity.x = ((target->x - (m_dst.x + m_dst.w /2)) / sqrt(pow(target->x - (m_dst.x + m_dst.w / 2), 2) + pow(target->y - (m_dst.y - m_dst.h / 2), 2))) * MaxVelocity;
	desiredVelocity.y = ((target->y - (m_dst.y - m_dst.h /2)) / sqrt(pow(target->x - (m_dst.x + m_dst.w / 2), 2) + pow(target->y - (m_dst.y - m_dst.h / 2), 2))) * MaxVelocity;

	SteeringForce.x = desiredVelocity.x - currentVelocity.x;
	SteeringForce.y = desiredVelocity.y - currentVelocity.y;

	SteeringForce.x = UTIL::Trunacate(SteeringForce.x, MaxForce);
	SteeringForce.y = UTIL::Trunacate(SteeringForce.y, MaxForce);

	moveVelocity(&nearPlayer);

	checkcollision();
}

bool enemy::move(SDL_Point* pos)
{
	bool up = false, down = false, left = false, right = false;
	SDL_Point buffer = { m_dst.x, m_dst.y };
	if (m_dst.x + m_dst.w /2 < pos->x)
	{
		left = true;
		right = false;
		m_dst.x = m_dst.x + speed * limitspeed(pos);
	}
	else if (m_dst.x + m_dst.w /2> pos->x)
	{
		right = true;
		left = false;
		m_dst.x = m_dst.x - speed * limitspeed(pos);
	}

	if (m_dst.y + m_dst.h /2 < pos->y)
	{
		down = true;
		up = false;
		m_dst.y = m_dst.y + speed * limitspeed(pos);
	}
	else if (m_dst.y + m_dst.h/2> pos->y)
	{
		up = true;
		down = false;
		m_dst.y = m_dst.y - speed * limitspeed(pos);
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

	if (m_dst.x + m_dst.w /2 == pos->x && m_dst.y + m_dst.h /2== pos->y)
	{
		std::cout << "reached a target.\n";
		path.erase(path.begin());
		return false;
	}
	else
		return true;
}

bool enemy::moveVelocity(SDL_Point* target)
{
	currentVelocity.x = UTIL::Trunacate(currentVelocity.x + SteeringForce.x, MaxVelocity);
	currentVelocity.y = UTIL::Trunacate(currentVelocity.y + SteeringForce.y, MaxVelocity);

	m_dst.x = m_dst.x + currentVelocity.x * limitspeed(target);
	m_dst.y = m_dst.y + currentVelocity.y * limitspeed(target);

	rotation = 180 + atan2(currentVelocity.y, currentVelocity.x) * 180 / 3.14;

	return true;
}

double enemy::limitspeed(SDL_Point* target)
{
	double dist = sqrt(pow(m_dst.x - target->x, 2) + pow(m_dst.y - target->y, 2));

	if (dist < 4)
		return dist / 4;
	else
		return 1.0;
}

void enemy::checkcollision()
{
	for (int i = 0; i < LevelManager::getInstance().getWallNum(); i++)
	{
		if (UTIL::AABBcollide(&m_dst, LevelManager::getInstance().getWall(i)->getRect()))
		{
			correctcollision(LevelManager::getInstance().getWall(i)->getRect());
		}
	}
}

void enemy::correctcollision(SDL_Rect* plat)
{
	if (m_dst.y + m_dst.w - currentVelocity.y <= plat->y)
	{
		m_dst.y = plat->y - m_dst.h - 1;
		currentVelocity.y = 0;
	}
	if (m_dst.y - currentVelocity.y >= plat->y + plat->h)
	{
		m_dst.y = plat->y + plat->h + 1;
		currentVelocity.y = 0;
	}
	if (m_dst.x + m_dst.w - currentVelocity.x <= plat->x)
	{
		m_dst.x = plat->x - m_dst.w - 1;
		currentVelocity.x = 0;
	}
	if (m_dst.x - currentVelocity.x >= plat->x + plat->w)
	{
		m_dst.x = plat->x + plat->w + 1;
		currentVelocity.x = 0;
	}
}

bool enemy::AI()
{
	switch (state)
	{
	case hunt:
	{
		hunting();
		break;
	}
	case search:
	{
		searching();
		break;
	}
	case wander:
	{
		wandering();
		break;
	}
	}


	return true;
}

bool enemy::wandering()
{
	speed = 1;
	if (look(&nearPlayer) == true)
	{
		speed = 4;
		wandergoal = 0;
		wanderplace = 0;
		wandertimer = 0;
		clearpath();
		state = hunt;
		return true;
	}
	else if (listen(&nearSound) == true)
	{
		speed = 4;
		wandergoal = 0;
		wanderplace = 0;
		wandertimer = 0;
		state = search;
		clearpath();
		if (ObjectManager::getInstance().getPathFinder()->findPath(&path, m_dst.x + m_dst.w /2, m_dst.y + m_dst.h /2, nearSound.x, nearSound.y))
		{
			return true;
		}
		else
		{
			state = wander;
			return true;
		}
		return true;
	}
	else
	{
		if (wandergoal == 0)
		{
			srand(time(NULL));

			random = rand();

			wandergoal = random % 60 + 60;

			bool invalid = true;

			while (invalid == true)
			{
				srand(random);

				random = rand();

				wanderplace = random % ObjectManager::getInstance().getPathFinder()->getNodeNum();

				std::cout << "wander place is " << wanderplace << std::endl;

				clearpath();
				if (ObjectManager::getInstance().getPathFinder()->getNode(wanderplace)->getpassable() == true)
				{
					SDL_Point buffer = { m_dst.x + m_dst.w /2, m_dst.y + m_dst.h /2};
					if (UTIL::distancePoint(ObjectManager::getInstance().getPathFinder()->getNode(wanderplace)->getPoint(), &buffer) < 200)
					{
						invalid = false;
					}
				}
			}

			ObjectManager::getInstance().getPathFinder()->findPath(&path, m_dst.x, m_dst.y, ObjectManager::getInstance().getPathFinder()->getNode(wanderplace)->getPoint()->x, ObjectManager::getInstance().getPathFinder()->getNode(wanderplace)->getPoint()->y);

			wandertimer = 0;

		}
		else
		{
			if (wandertimer > wandergoal)
			{
				if (!path.empty())
				{
					if (move(&path.front()))
					{
					}
					else
					{
						clearpath();
						wandergoal = 0;
						wanderplace = 0;
						wandertimer = 0;
					}
				}
				else
				{
					wanderplace = 0;
					wandertimer = 0;
					wandergoal = 0;
				}
			}
			else
			{
				wandertimer++;
			}
		}
	}
	return true;
}

bool enemy::hunting()
{
	if (look(&nearPlayer) == true)
	{
		clearpath();
		SDL_Point buffer = { m_dst.x + m_dst.w /2, m_dst.y + m_dst.h /2};
		if (UTIL::distancePoint(&buffer, &nearPlayer) < 100)
		{
			seek(&nearPlayer);
			rotation = angle;
		}
		else if (ObjectManager::getInstance().getPathFinder()->findPath(&path, m_dst.x + m_dst.w /2, m_dst.y + m_dst.h /2, nearPlayer.x, nearPlayer.y))
		{
			if (path.size() > 1)
			{
				path.erase(path.begin());
			}
			seek(&path.front());
			rotation = angle;
		}
	}
	else
	{
		clearpath();
		SDL_Point buffer = { m_dst.x + m_dst.w /2, m_dst.y + m_dst.h /2 };
		if (UTIL::distancePoint(&buffer, &nearPlayer) < 58)
		{
			clearpath();
			state = wander;
			return true;
		}
		else if (ObjectManager::getInstance().getPathFinder()->findPath(&path, m_dst.x + m_dst.w /2, m_dst.y + m_dst.h /2, nearPlayer.x, nearPlayer.y))
		{
			if (path.size() > 1)
			{
				path.erase(path.begin());
			}
			seek(&path.front());
			rotation = angle;
		}
	}
	return false;
}

bool enemy::searching()
{
	if (look(&nearPlayer) == true)
	{
		state = hunt;
		return true;
	}
	else if (listen(&nearSound) == true)
	{
		std::cout << "hear.\n";
		clearpath();
		if (ObjectManager::getInstance().getPathFinder()->findPath(&path, m_dst.x + m_dst.w /2, m_dst.y + m_dst.h /2, nearSound.x, nearSound.y))
		{
			return true;
		}
		else
		{
			state = wander;
			return true;
		}
	}
	else
	{
		if (ObjectManager::getInstance().getPathFinder()->findPath(&path, m_dst.x + m_dst.w / 2, m_dst.y + m_dst.h / 2, nearSound.x, nearSound.y))
		{

		}
		SDL_Point buffer = { m_dst.x + m_dst.w / 2, m_dst.y + m_dst.h /2};
		
		move(&path.front());


		if(UTIL::distancePoint(&nearSound, &buffer) < 58)
		{
			clearpath();
			state = wander;
			return true;
		}
	}
	return false;
}

enemy::~enemy()
{
}
