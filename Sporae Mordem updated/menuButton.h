#pragma once
#include "button.h"
class menuButton :
	public button
{
public:
	void onClick();
	menuButton(int x, int y, int w, int h, int id);
	~menuButton();
};

