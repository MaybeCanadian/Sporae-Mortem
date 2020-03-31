#pragma once
#include <SDL.h>
#define MENU 0
#define GAME 1
#define PAUSE 2
#define SETTINGS 3
#define LOSE 4
//this is a virtual class
class State
{
public:
	State();
	virtual void update() = 0;
	virtual void handleEvents() = 0;
	virtual void render() = 0;
	virtual void enter() = 0;
	virtual void exit() = 0;
	virtual ~State();
};

#include "engine.h"
#include "StateGame.h"
#include "StateMenu.h"
#include "StatePause.h"
#include "StateSettings.h"
#include "StateLose.h"
