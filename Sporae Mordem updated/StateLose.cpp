#include "StateLose.h"



StateLose::StateLose()
{
}


StateLose & StateLose::getInstance()
{
	static StateLose instance;
	return instance;
}

void StateLose::update()
{
	UIManager::getInstance().update();
	InputManager::getInstance().update();
}

void StateLose::render()
{
	UIManager::getInstance().renderLOSE();
	TextureManager::getInstance().RenderPresent();
}

void StateLose::handleEvents()
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
				StateManager::getInstance().changeState(MENU);
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

void StateLose::enter()
{
	ObjectManager::getInstance().getPlayerManager()->clearPlayers();
	AudioManager::getInstance().stopALL();
	UIManager::getInstance().addButton(412, 400, 200, 80, 4);
}

void StateLose::exit()
{
	UIManager::getInstance().clearButtons();
}

StateLose::~StateLose()
{
}
