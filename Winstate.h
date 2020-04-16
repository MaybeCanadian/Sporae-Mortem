#pragma once
#include "State.h"
class Winstate :
	public State
{
private:
	Winstate();
public:
	static Winstate& getInstance();
	void update();
	void render();
	void handleEvents();
	void enter();
	void exit();
	~Winstate();
};

