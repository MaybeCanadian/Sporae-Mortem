#pragma once
#include "button.h"
class PlayButton :
	public button
{
public:
	void onClick();
	PlayButton(int x, int y, int w, int h, int id);
	~PlayButton();
};

