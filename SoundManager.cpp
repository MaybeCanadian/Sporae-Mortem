#include "SoundManager.h"

SoundManager::SoundManager()
{
	cout << "Sound manager constucted" << endl;
}


SoundManager & SoundManager::getInstance()
{
	static SoundManager insatnce;
	return insatnce;
}

void SoundManager::soundCreate(int x, int y, int radius, int duration)
{
	sounds.push_back(new sound(x, y, radius, duration));
}

bool SoundManager::soundDetect(double radius, SDL_Rect position, sound soundInput)
{
	double difference;
	difference = sqrt((position.x - soundInput.getSoundX() * (position.x - soundInput.getSoundX() + (position.y) - soundInput.getSoundY()) * (position.y) - soundInput.getSoundY()));
	if (difference >= (radius + soundInput.getSoundRadius()))
		return true;
	return false;
}

vector<sound*> SoundManager::getSoundVector()
{
	return sounds;
}


SoundManager::~SoundManager()
{
}
