#include "StateMenu.h"

StateMenu::StateMenu()
{
}


StateMenu & StateMenu::getInstance()
{
	static StateMenu instance;
	return instance;
}

void StateMenu::update()
{
	UIManager::getInstance().update();
	InputManager::getInstance().update();
}

void StateMenu::handleEvents()
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
				engine::getInstance().quit();
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

void StateMenu::render()
{
	UIManager::getInstance().rednerMENU();
	TextureManager::getInstance().RenderPresent();
}

void StateMenu::enter()
{
	AudioManager::getInstance().playMusic(1);
	UIManager::getInstance().addButton(312, 100, 400, 100, 2);
	UIManager::getInstance().addButton(312, 300, 400, 100, 3);
	std::cout << "entering Menu State.\n";
}

void StateMenu::exit()
{
	UIManager::getInstance().clearButtons();
	LevelStateManager::getInstance().changeLevel(0);
	ObjectManager::getInstance().getPlayerManager()->addPlayer(4*GRID, 3*GRID);
	TextureManager::getInstance().RenderClear();
	std::cout << "exiting Menu state.\n";
}

StateMenu::~StateMenu()
{
}
