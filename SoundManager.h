#pragma once
#include "basic_includes.h"
#include "sound.h"
#include "Enemy.h"

class sound;
class Enemy;

class SoundManager
{
private:
	SoundManager();
	vector<sound*> sounds;
public:
	static SoundManager& getInstance(); //singleton for the sound manager
	void soundCreate(int x, int y, int radius, int duration); //makes a sound, sounds last fo 1 frame only for detection purposes
	bool soundDetect(double radius, SDL_Rect position, sound soundInput); //detects if a sound is within a certain enemy radius
	vector<sound*> getSoundVector();
	~SoundManager();
};

