#include "SoundManager.h"

SoundManager::SoundManager()
{
}

void SoundManager::soundsCreate(int x, int y, int radius, int duration)
{
	s_vSounds.push_back(new sounds(x, y, radius, duration));
}

bool SoundManager::DetectSounds(double radius, SDL_Rect * position, SDL_Point * nearest)
{
	SDL_Point buffer;
	int near = -1;
	float neardist = 100000000000;
	buffer.x = position->x + position->w / 2;
	buffer.y = position->y + position->h / 2;
	for (int i = 0; i < (int)s_vSounds.size(); i++) //check through all sounds
	{
		if (UTIL::CircleCollide(&buffer, radius, s_vSounds[i]->getPos(), s_vSounds[i]->getRadius()))
		{
			if (UTIL::distancePoint(&buffer, s_vSounds[i]->getPos()) < neardist)
			{
				near = i;
				neardist = UTIL::distancePoint(&buffer, s_vSounds[i]->getPos());
			}
		}
	}

	if (near != -1) //if a sound was detected, return it was and send the point closest to the object
	{
		nearest->x = s_vSounds[near]->getPos()->x;
		nearest->y = s_vSounds[near]->getPos()->y;
		return true;
	}
	else return false;
}

void SoundManager::update()
{
	if (!s_vSounds.empty()) //updates all sounds
	{
		for (int i = 0; i < (int)s_vSounds.size(); i++)
		{
			s_vSounds[i]->update();
			if (s_vSounds[i]->getActive() == false)
			{
				delete s_vSounds[i];
				s_vSounds[i] = nullptr;
			}
		}
	}

	if (!s_vSounds.empty()) //removes all deleted sounds
		for (int i = 0; i < (int)s_vSounds.size(); i++)
			if (s_vSounds[i] == nullptr)
				s_vSounds.erase(s_vSounds.begin()+i);
}

bool SoundManager::initManager()
{
	//nothing to init right now
	std::cout << "soundManager init.\n";
	return true;
}

void SoundManager::clean()
{
	s_vSounds.clear();
	s_vSounds.shrink_to_fit();
	std::cout << "soundManager clean.\n";
}


SoundManager::~SoundManager()
{
}
