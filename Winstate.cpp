#include "Winstate.h"



Winstate::Winstate()
{
}

Winstate & Winstate::getInstance()
{
	static Winstate instance;
	return instance;
}

void Winstate::update()
{
	InputManager::getInstance().update();
}

void Winstate::render()
{
	UIManager::getInstance().renderWIN();
	TextureManager::getInstance().RenderPresent();
}

void Winstate::handleEvents()
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

void Winstate::enter()
{
	UIManager::getInstance().addButton(WIDTH / 2 - 100, HEIGHT / 2 + HEIGHT / 4 - 50, 200, 100, 4);
	AudioManager::getInstance().stopALL();
}

void Winstate::exit()
{
	UIManager::getInstance().clearButtons();
	ObjectManager::getInstance().getPlayerManager()->clearPlayers();
}


Winstate::~Winstate()
{
}
