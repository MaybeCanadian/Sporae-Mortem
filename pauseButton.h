#pragma once
#include "button.h"

class pauseButton :
	public button
{
public:
	void onClick();
	pauseButton(int x, int y, int w, int h, int id);
	~pauseButton();
};

