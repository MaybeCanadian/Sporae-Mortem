#include "AudioManager.h"


AudioManager::AudioManager()
{
}


AudioManager & AudioManager::getInstance()
{
	static AudioManager instance;
	return instance;
}

bool AudioManager::initManager()
{
	if (Mix_Init(MIX_INIT_MP3) != 0) //this initialises all the need parts for audio
	{
		Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 8192);
		Mix_AllocateChannels(32);
		bgm = Mix_LoadMUS("sound/bg.mp3");
		Mix_Volume(0, MIX_MAX_VOLUME / 2);
		std::cout << "audioManager init.\n";
		return true;
	}
	else
		return false;
}

AudioManager::~AudioManager()
{
}

int AudioManager::addSound(std::string input)
{
	const char * buffer = input.c_str();
	sounds.push_back(Mix_LoadWAV(buffer));
	if (sounds[sounds.size() - 1] == nullptr)
	{
		std::cout << "error loading sound chunk. postition " << sounds.size() << "\n";
	}
	return (int)sounds.size() - 1;
}

int AudioManager::playSound(int ID, int chanel, int loop)
{
	int num;
	num = Mix_PlayChannel(chanel, sounds[ID], loop);
	return num;
}

int AudioManager::playSoundEX(int ID, int chanel, int loop, int time)
{
	int num;
	num = Mix_PlayChannelTimed(chanel, sounds[ID], loop, time);
	std::cout << "test" << std::endl;
	return num;
}

void AudioManager::playMusic()
{
	Mix_PlayMusic(bgm, -1);
}

void AudioManager::pausebgm()
{
	Mix_PauseMusic();
}

bool AudioManager::chanelActive(int chanel)
{
	return Mix_Playing(chanel);
}

void AudioManager::haltChanel(int chanel)
{
	Mix_HaltChannel(chanel);
}

void AudioManager::fadeChanel(int chanel, int time)
{
	Mix_FadeOutChannel(chanel, time);
}

int AudioManager::fadeInChanel(int ID, int chanel, int loop, int time)
{
	int num;
	num = Mix_FadeInChannel(chanel, sounds[ID], loop, time);
	return num;
}

void AudioManager::clean()
{
	sounds.clear();
	sounds.shrink_to_fit();
	std::cout << "audioManager clean.\n";
}

