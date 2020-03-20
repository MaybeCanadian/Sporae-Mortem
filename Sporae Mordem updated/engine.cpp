#include "engine.h"

engine::engine()
{
	m_bRunning = false;
}

bool engine::init(const char * title, int xpos, int ypos, int width, int height, int flags)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		if (TextureManager::getInstance().initManager(title, xpos, ypos, width, height, flags))
		{
			std::cout << std::endl;
			if (AudioManager::getInstance().initManager())
			{
				std::cout << std::endl;
				if (InputManager::getInstance().initManager())
				{
					std::cout << std::endl;
					if (StateManager::getInstance().initManager())
					{
						std::cout << std::endl;
						if (ObjectManager::getInstance().initManager())
						{
							std::cout << std::endl;
							if (UIManager::getInstance().initManager())
							{
								std::cout << std::endl;
								if (LevelManager::getInstance().initManager())
								{
									std::cout << std::endl;
								}
								else return false;
							}
							else return false;
						}
						else return false;
					}
					else return false;
				} 
				else return false;
			}
			else return false;
		}
		else return false;
	}
	else return false;

	std::cout << "All managers init.\nStarting engine.\n\n\n";
	m_fps = (Uint32)round(1 / (double)FPS * 1000);
	m_bRunning = true;

	return true;
}

void engine::wake()
{
	m_start = SDL_GetTicks();
}

void engine::sleep()
{
	m_end = SDL_GetTicks();
	m_delta = m_end - m_start;
	if (m_delta < m_fps)
		SDL_Delay(m_fps - m_delta);
}

void engine::clean()
{
	TextureManager::getInstance().clean();
	std::cout << std::endl;
	AudioManager::getInstance().clean();
	std::cout << std::endl;
	ObjectManager::getInstance().clean();
	std::cout << std::endl;
	InputManager::getInstance().clean();
	std::cout << std::endl;
	UIManager::getInstance().clean();
}


engine & engine::getInstance()
{
	static engine instance;
	return instance;
}

int engine::run()
{
	if (init("GAME1007_SDL_Setup", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0) == false)
		return 1;
	while (m_bRunning)
	{
		wake();
		StateManager::getInstance().handleEvents();
		StateManager::getInstance().update();
		StateManager::getInstance().render();
		if (m_bRunning)
			sleep();
	}
	clean();
	return 0;
}

void engine::quit()
{
	m_bRunning = false;
}

engine::~engine()
{
}
