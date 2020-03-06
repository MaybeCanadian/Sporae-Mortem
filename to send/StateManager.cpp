#include "StateManager.h"

StateManager::StateManager()
{
}

void StateManager::switchState(int newState)
{
	switch (state) //exits old state
	{
	case MENU:
		StateMenu::getInstance().exit();
		break;
	case GAME:
		StateGame::getInstance().exit();
		break;
	case PAUSE:
		StatePause::getInstance().exit();
		break;
	}

	state = newState;

	switch (state) //enters new state
	{
	case MENU:
		StateMenu::getInstance().enter();
		break;
	case GAME:
		StateGame::getInstance().enter();
		break;
	case PAUSE:
		StatePause::getInstance().enter();
		break;
	}
}


StateManager & StateManager::getInstance()
{
	static StateManager instance;
	return instance;
}

int StateManager::getState()
{
	return state;
}

void StateManager::changeState(int input)
{
	switch (state)
	{
	case MENU:
		switch (input)
		{
			case GAME:
			{
				switchState(GAME);
				break;
			}
		}
		break;
	case GAME:
		switch (input)
		{
			case PAUSE:
			{
				switchState(PAUSE);
				break;
			}
		}
		break;
	case PAUSE:
		switch (input)
		{
			case MENU:
			{
				switchState(MENU);
				break;
			}
			case GAME:
			{
				switchState(GAME);
				break;
			}
		}
		break;
	}
}

bool StateManager::initManager()
{
	state = 0;
	StateMenu::getInstance().enter();
	std::cout << "stateManager init.\n";
	return true;
}

void StateManager::clean()
{
	//nothing needs to be cleaned as of yet
	std::cout << "stateManager clean.\n";
}

void StateManager::update()
{
	switch (state)
	{
	case MENU:
		StateMenu::getInstance().update();
		break;
	case GAME:
		StateGame::getInstance().update();
		break;
	case PAUSE:
		StatePause::getInstance().update();
		break;
	}
}

void StateManager::render()
{
	switch (state)
	{
	case MENU:
		StateMenu::getInstance().render();
		break;
	case GAME:
		StateGame::getInstance().render();
		break;
	case PAUSE:
		StatePause::getInstance().render();
		break;
	}
}

void StateManager::handleEvents()
{
	switch (state)
	{
	case MENU:
		StateMenu::getInstance().handleEvents();
		break;
	case GAME:
		StateGame::getInstance().handleEvents();
		break;
	case PAUSE:
		StatePause::getInstance().handleEvents();
		break;
	}
}

StateManager::~StateManager()
{
}
