#pragma once
#include "engine.h"
#include <SDL_mixer.h>

class AudioManager
{
private:
	std::vector<Mix_Chunk*> sounds;
	int soundChunkID[5];
	Mix_Music* bgm,*bgm2;
private:
	AudioManager();
public:
	static AudioManager& getInstance();
	bool initManager(); //inits the manager
	int addSound(std::string input); //adds sound, returns call id
	int playSound(int ID, int chanel, int loop); //plays sound, needs call id, chanel to play in, numbe of times looped
	int playSoundEX(int ID, int chanel, int loop, int time); //plays sound at id, in chanel looped lopp times, for a duration of time per loop
	void playMusic(int);
	void pausebgm();
	void resumebgm();
	bool chanelActive(int chanel);
	void haltChanel(int chanel);
	void fadeChanel(int chanel, int time);
	int fadeInChanel(int ID, int chanel, int loop, int time);
	void changeVolume(int chanel, int volume);
	void clean(); //cleans manager and dealocates memory
	~AudioManager();
};

