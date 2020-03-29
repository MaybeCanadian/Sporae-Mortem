#pragma once
#include "State.h"
class StateSettings :
	public State
{
private:
	StateSettings();
public:
	static StateSettings& getInstance();
	void update();
	void render();
	void handleEvents();
	void enter();
	void exit();
	~StateSettings();
};

