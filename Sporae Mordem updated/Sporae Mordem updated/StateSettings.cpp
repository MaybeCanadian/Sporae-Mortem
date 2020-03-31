#include "StateSettings.h"



StateSettings::StateSettings()
{
}

StateSettings & StateSettings::getInstance()
{
	static StateSettings instance;
	return instance;
}

void StateSettings::update()
{
}

void StateSettings::render()
{
}

void StateSettings::handleEvents()
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

void StateSettings::enter()
{

}

void StateSettings::exit()
{
}


StateSettings::~StateSettings()
{
}
