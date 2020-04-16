#include "StatePause.h"

StatePause::StatePause()
{
}

StatePause & StatePause::getInstance()
{
	static StatePause instance;
	return instance;
}

void StatePause::update()
{
	UIManager::getInstance().update();
	InputManager::getInstance().update();
}

void StatePause::render()
{
	UIManager::getInstance().renderGAME();
	LevelManager::getInstance().render();
	ObjectManager::getInstance().render();
	UIManager::getInstance().renderPAUSE();
	TextureManager::getInstance().RenderPresent();
}

void StatePause::handleEvents()
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
				StateManager::getInstance().changeState(GAME);
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

void StatePause::enter()
{
	std::cout << "entering Pause state.\n";
	AudioManager::getInstance().stopALL();
	LabelManager::getInstance().setActive(true);
	UIManager::getInstance().addButton(412, 200, 200, 80, 1);
	UIManager::getInstance().addButton(412, 400, 200, 80, 4);
}

void StatePause::exit()
{
	LabelManager::getInstance().setActive(false);
	std::cout << "exiting Pause state.\n";
	UIManager::getInstance().clearButtons();
	AudioManager::getInstance().resumebgm();
}

StatePause::~StatePause()
{
}
