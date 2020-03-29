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
		soundChunkID[0]=addSound("sound/bg.mp3");
		soundChunkID[1]=addSound("sound/catch.mp3");
		soundChunkID[2]=addSound("sound/door_open_sound.mp3");
		soundChunkID[3]=addSound("sound/Run.mp3");
		soundChunkID[4]=addSound("sound/stone.mp3");
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

void AudioManager::playSound(int ID, int chanel, int loop)
{
	Mix_PlayChannel(chanel, sounds[ID], loop);
}

void AudioManager::clean()
{
	sounds.clear();
	sounds.shrink_to_fit();
	std::cout << "audioManager clean.\n";
}

