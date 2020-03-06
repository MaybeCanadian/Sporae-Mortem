#pragma once
#include "State.h"
class StatePause :
	public State
{
private:
	StatePause();
public:
	static StatePause& getInstance();
	void update();
	void render();
	void handleEvents();
	void enter();
	void exit();
	~StatePause();
};

