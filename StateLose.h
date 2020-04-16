#pragma once
#include "State.h"
class StateLose :
	public State
{
private:
	StateLose();
	int sound;
public:
	static StateLose& getInstance();
	void update();
	void render();
	void handleEvents();
	void enter();
	void exit();
	~StateLose();
};

