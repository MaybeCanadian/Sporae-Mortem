#pragma once
#include "State.h"
class StateGame :
	public State
{
private:
	StateGame();
public:
	static StateGame& getInstance();
	void update();
	void render();
	void handleEvents();
	void enter();
	void exit();
	~StateGame();
};

