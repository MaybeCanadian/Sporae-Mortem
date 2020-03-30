#include "StateGame.h"

StateGame::StateGame()
{
}

StateGame & StateGame::getInstance()
{
	static StateGame instance;
	return instance;
}

void StateGame::update()
{
	ObjectManager::getInstance().update();
	LevelManager::getInstance().update();
	InputManager::getInstance().update();
}

void StateGame::render()
{
	UIManager::getInstance().renderGAME();
	LevelManager::getInstance().render();
	ObjectManager::getInstance().render();
	LabelManager::getInstance().render();
	TextureManager::getInstance().RenderPresent();
}

void StateGame::handleEvents()
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT: // User pressed window's 'x' button.
			engine::getInstance().quit();
			break;
		case SDL_KEYDOWN: // records a key press event
			if (event.key.keysym.sym == SDLK_ESCAPE)
				StateManager::getInstance().changeState(PAUSE);
			break;
		case SDL_MOUSEBUTTONDOWN: //records a mouse down event
			InputManager::getInstance().mouseDown(event.button);
			break;
		case SDL_MOUSEBUTTONUP: //records a mouse up event
			InputManager::getInstance().mouseUp(event.button);
			break;
		}
	}
}

void StateGame::enter()
{
	AudioManager::getInstance().playMusic(0);
	std::cout << "entering Game state.\n";
}

void StateGame::exit()
{
	AudioManager::getInstance().pausebgm();
	TextureManager::getInstance().RenderClear();
	std::cout << "exiting Game state.\n";
}

StateGame::~StateGame()
{
}
