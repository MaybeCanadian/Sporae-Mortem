#include "enemy.h"

bool enemy::look(SDL_Point * nearPlayer)
{
	double neardist = 1000;
	for (int i = 0; i < ObjectManager::getInstance().getPlayerManager()->getNumPlayers(); i++)
	{
		double bufferRadius = ObjectManager::getInstance().getPlayerManager()->getPlayers(i)->getDetctRange();
		SDL_Point bufferPoint = { ObjectManager::getInstance().getPlayerManager()->getPlayers(i)->getRect()->x + ObjectManager::getInstance().getPlayerManager()->getPlayers(i)->getRect()->w / 2,
			ObjectManager::getInstance().getPlayerManager()->getPlayers(i)->getRect()->y + ObjectManager::getInstance().getPlayerManager()->getPlayers(i)->getRect()->h / 2 };
		SDL_Point bufferEnemy = { m_dst.x + m_dst.w, m_dst.y + m_dst.h / 2 };
		if (UTIL::CircleCollide(&bufferEnemy, m_dst.w, &bufferPoint, bufferRadius))
		{
			int deltaX = m_dst.x - bufferPoint.x;
			int deltaY = m_dst.y - bufferPoint.y;

			double angle = atan2(deltaY, deltaX);
			angle = angle * 180 / 3.14;

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
						std::cout << "in view.\n";
						int dist = sqrt(pow(bufferEnemy.x - bufferPoint.x, 2) + pow(bufferEnemy.y - bufferPoint.y, 2));
						if (dist < neardist)
						{
							neardist = dist;
							nearPlayer->x = ObjectManager::getInstance().getPlayerManager()->getPlayers(i)->getRect()->x;
							nearPlayer->y = ObjectManager::getInstance().getPlayerManager()->getPlayers(i)->getRect()->y;
						}
					}
				}
			}
			else if (maxangle < minangle)
			{
				if (angle > 0 && angle < maxangle)
				{
					if (checkwalls(&bufferPoint) == false)
					{
						std::cout << "in view.\n";
						int dist = sqrt(pow(bufferEnemy.x - bufferPoint.x, 2) + pow(bufferEnemy.y - bufferPoint.y, 2));
						if (dist < neardist)
						{
							neardist = dist;
							nearPlayer->x = ObjectManager::getInstance().getPlayerManager()->getPlayers(i)->getRect()->x;
							nearPlayer->y = ObjectManager::getInstance().getPlayerManager()->getPlayers(i)->getRect()->y;
						}
					}
					else if (angle < 360 && angle > minangle)
					{
						if (checkwalls(&bufferPoint) == false)
						{
							std::cout << "in view.\n";
							int dist = sqrt(pow(bufferEnemy.x - bufferPoint.x, 2) + pow(bufferEnemy.y - bufferPoint.y, 2));
							if (dist < neardist)
							{
								neardist = dist;
								nearPlayer->x = ObjectManager::getInstance().getPlayerManager()->getPlayers(i)->getRect()->x;
								nearPlayer->y = ObjectManager::getInstance().getPlayerManager()->getPlayers(i)->getRect()->y;
							}
						}
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

enemy::enemy(int x, int y, int type, int id)
{
	m_dst = { x, y, 30, 30 };
	lookRange = 300;
	textureID = id;
	this->type = type;
	speed = 2;
	pathtarget.x = m_dst.x;
	pathtarget.y = m_dst.y;
	rotation = 90 * type;
	MaxVelocity = 4;
	MaxForce = 2;
	chase = false;
	search = false;
	wander = false;
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
	TextureManager::getInstance().DrawEx(textureID, &m_dst, NULL, rotation - 90, NULL, SDL_FLIP_NONE);
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
	if(!path.empty())
	{
		pathtarget = path[0];
		seek(&pathtarget);

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
	desiredVelocity.x = ((target->x - m_dst.x) / sqrt(pow(target->x - m_dst.x, 2) + pow(target->y - m_dst.y, 2))) * MaxVelocity;
	desiredVelocity.y = ((target->y - m_dst.y) / sqrt(pow(target->x - m_dst.x, 2) + pow(target->y - m_dst.y, 2))) * MaxVelocity;

	SteeringForce.x = desiredVelocity.x - currentVelocity.x;
	SteeringForce.y = desiredVelocity.y - currentVelocity.y;

	SteeringForce.x = UTIL::Trunacate(SteeringForce.x, MaxForce);
	SteeringForce.y = UTIL::Trunacate(SteeringForce.y, MaxForce);

	moveVelocity(&nearPlayer);
}

bool enemy::move(SDL_Point* pos)
{
	bool up = false, down = false, left = false, right = false;
	SDL_Point buffer = { m_dst.x, m_dst.y };
	if (m_dst.x < pos->x)
	{
		left = true;
		if (UTIL::distancePoint(&buffer, &pathtarget) > 2)
			m_dst.x = m_dst.x + speed;
		else
			m_dst.x = m_dst.x + 1;
	}
	else if (m_dst.x > pos->x)
	{
		right = true;
		if (UTIL::distancePoint(&buffer, &pathtarget) > 2)
			m_dst.x = m_dst.x - speed;
		else
			m_dst.x = m_dst.x - 1;
	}

	if (m_dst.y < pos->y)
	{
		down = true;
		if (UTIL::distancePoint(&buffer, &pathtarget) > 2)
			m_dst.y = m_dst.y + speed;
		else
			m_dst.y = m_dst.y + 1;
	}
	else if (m_dst.y > pos->y)
	{
		up = true;
		if (UTIL::distancePoint(&buffer, &pathtarget) > 2)
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

	if (dist < 10)
		return dist / 10;
	else
		return 1.0;
}

bool enemy::AI()
{
	if (chase == true) //you are currently after them
	{
		std::cout << "in chase.\n";
		//yes

		if (look(&nearPlayer)) //can you still see them?
		{
			//yes
			if (sqrt(pow(nearPlayer.x - m_dst.x, 2) + pow(nearPlayer.y - m_dst.y, 2)) < GRID) //are you close to them?
			{
				std::cout << "near player.\n";
				seek(&nearPlayer); //yes, then why not just go to them by seeking?
			}
			else
			{
				//not close then
				//do you have a path to them right now?
				if (havePlayerPath == true)
				{
					//great but is it still relevant we should check every 10 frames
					if (playerpathcounter > 60)
					{
						//maybe we should check the path is still towards the player
						if (ObjectManager::getInstance().getPathFinder()->findPath(&path, m_dst.x, m_dst.y, nearPlayer.x, nearPlayer.y))
						{
							//cool we have a fresh path
							playerpathcounter = 0;
							havePlayerPath = true;
							followpath(); //lets follow it
							return true;
						}
						else
						{
							//we are unable to get a path?
							//they must be glitched
							chase = false;
							wander = true;
							havePlayerPath = false;
							//lets forget about it then
							return true;
						}
					}
					else
					{
						//okay the path is still valid for now
						//lets follow it
						playerpathcounter++;
						havePlayerPath = true;
						followpath();
						return true;
					}
				}
				else
				{
					//we dont have a path then?
					//okay, lets find a new path
					if (ObjectManager::getInstance().getPathFinder()->findPath(&path, m_dst.x, m_dst.y, nearPlayer.x, nearPlayer.y)) //no, can you path there?
					{
						//yes you can
						//okay so why not follow the path
						playerpathcounter = 0;
						followpath();
						return true;
					}
					else
					{
						//no I can't path there
						std::cout << "ubable to reach the player.\n";
						chase = false;
						havePlayerPath = false;
						return true;

					}
				}
			}

		}
		else
		{
			std::cout << "test" << std::endl;
			//no
			//okay can you hear anything near you?
			if (listen(&nearSound))
			{
				checkedsound = false; //haven't checked it propably
				//yes you can
				//okay, is this sound close to you?
				if (sqrt(pow(m_dst.x - nearSound.x, 2) + pow(m_dst.y - nearSound.y, 2)) < 10)
				{
					//yes
					//you must be on top of it
					checkedsound = true; //you have checked it then
					heardSomething = false; //you haven't heard a new sound then
					haveSoundPath = false;
					clearpath();
					//take another look then
					return true;
				}
				else
				{
					//no
					// then maybe go to the sound
					heardSomething = true; //you heard it
					checkedsound = false; //need to check it out
					haveSoundPath = false;
					search = true; //start search mode
					chase = false; //stop chasing then
					return true;
				}
			}
			else
			{
				//nothing seems to be around you
				//did you have a sound you needed to checkout?
				if (heardSomething == true)
				{
					//yes you did
					//have you already checked it?
					if (checkedsound == false)
					{
						//no you haven't
						//you should check it out then
						search = true; //start searching
						chase = false; //stop chasing
						return true;
					}
					else
					{
						//you have checked it out already?
						//then you haven't heard anything new
						//I guess wander
						chase = false; //stop chasing
						wander = true; //start wandering
						clearpath();
						return true;
					}
				}
				else
				{
					//no nothing to look at
					//I guess you have nothing else to do
					//wander then
					chase = false;
					wander = true;
					return true;
				}
			}
		}
	}
	else
	{
		//no
		//so what were you doing if not chasing?

		if (search == true) //okay are you searching for something ie sound?
		{
			//yes you are
			//why not check if something is in front of you?
			if (look(&nearPlayer))
			{
				//oh look, something is there
				//maybe chase it
				haveSoundPath = false;
				chase = true; //start chasing
				search = false; //stop searching
				return true;
			}
			else
			{
				//okay, can't see anything, back to searching
				//just checking, no new sounds nearby right?
				if (listen(&nearSound))
				{
					//oh there is?
					//maybe you should be checking that out instead
					heardSomething = true;
					checkedsound = false;
					haveSoundPath = false;
					return true;
				}
				else
				{
					//no other sounds nearby then
					//you have a sound to find right?
					if (heardSomething == true)
					{
						//okay just checking
						//okay, is the sound close to you?
						if (sqrt(pow(m_dst.x - nearSound.x, 2) + pow(m_dst.y - nearSound.y, 2)) < 10)
						{
							//yes it is
							//you must be at the sound stop searching for it
							heardSomething = false; //no new sound
							checkedsound = true; //checked the old one
							haveSoundPath = false;
							clearpath();
							//maybe check agian for a new sound
							return true;
						}
						else
						{
							//no it isn't
							//okay, you should go to the sound
							//do you have a path there?
							if (haveSoundPath == true)
							{
								//cool, you should follow it
								followpath(); //follow the path
								return true;
							}
							else
							{
								//no path yet
								//maybe find a path
								clearpath();
								if (ObjectManager::getInstance().getPathFinder()->findPath(&path, m_dst.x, m_dst.y, nearSound.x, nearSound.y))
								{
									//you found a path, great
									haveSoundPath = true; //we have a path now
									return true;
								}
								else
								{
									//you can't find a path?
									//odd must be outside of the map
									heardSomething = false;
									checkedsound = false;
									//lets just forget about that sound
									return true;
								}
							}
						}
					}
					else
					{
						//you don't have a sound you are looking for and there's no new ones
						//i guess wander
						search = false; //stop searching
						wander = true; //start wandering
						return true;
					}
				}
			}

		}
		else if(wander == true)
		{
			//no you aren't
			//and you dont see anything infront of you?
			if (look(&nearPlayer))
			{
				//wait you do, then chase it
				havePlayerPath = false;
				clearpath();
				chase = true;
				wander = false;
				return true;
			}
			else
			{
				//okay you dont see anything
				//do you hear anything?
				if (listen(&nearSound))
				{
					//you do, why not check it out?
					heardSomething = true; //you heard something
					checkedsound = false;//haven't checked yet
					haveSoundPath = false;
					clearpath();
					wander = false;//no longer wandering
					search = true;//now you are searching
					return true;
				}
				else
				{
					//okay you didn't see or hear anything
					//i guess wander now
					wandering();
					return true;
				}
			}
		}
	}
	//if we are here that means everything is false
	wander = true; //we'll just start with wandering
	return true;
}

bool enemy::wandering()
{
	return true;
}

enemy::~enemy()
{
}
