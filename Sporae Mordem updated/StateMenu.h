#pragma once
#include "State.h"

class StateMenu :
	public State
{
private:
	StateMenu();
public:
	static StateMenu& getInstance();
	void update();
	void handleEvents();
	void render();
	void enter();
	void exit();
	~StateMenu();
};

