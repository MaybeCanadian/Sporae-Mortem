#pragma once
#include "ObjectManager.h"
#include "sounds.h"

class sounds;
class SoundManager
{
private:
	std::vector<sounds*> s_vSounds;
public:
	SoundManager();
	void soundsCreate(int x, int y, int radius, int duration); //adds a new sound at the point with a certain radius
	bool DetectSounds(double radius, SDL_Rect* position, SDL_Point* nearest); //checks all sounds, returns if it heard any and stores the nearest sound in nearest, nothing happens if none detected
	void update(); //updates the sounds
	bool initManager(); //inits the manager
	void clean(); //cleans the manager
	~SoundManager();
};

