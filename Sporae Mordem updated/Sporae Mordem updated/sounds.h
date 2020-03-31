#pragma once
#include "SoundManager.h"

class sounds
{
private:
	SDL_Point position;
	double radius;
	int duration;
	int time;
	bool s_active;
public:
	const double getRadius(); //returns the sounds radius of effect
	const SDL_Point* getPos(); //returns the origion of the sound
	sounds(int x, int y, double rad, int dur); //sound needs x and y of origion and sound radius
	void update();
	void render();
	bool getActive();
	~sounds();
};

