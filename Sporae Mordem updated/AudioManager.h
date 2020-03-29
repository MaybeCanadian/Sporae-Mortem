#pragma once
#include "engine.h"
#include <SDL_mixer.h>

class AudioManager
{
private:
	std::vector<Mix_Chunk*> sounds;
	int soundChunkID[5];
private:
	AudioManager();
public:
	static AudioManager& getInstance();
	bool initManager(); //inits the manager
	int addSound(std::string input); //adds sound, returns call id
	void playSound(int ID, int chanel, int loop); //plays sound, needs call id, chanel to play in, numbe of times looped
	void clean(); //cleans manager and dealocates memory
	~AudioManager();
};

