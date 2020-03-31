#pragma once
#include "button.h"
class settingsbutton :
	public button
{
public:
	void onClick();
	settingsbutton(int x, int y, int w, int h, int id);
	~settingsbutton();
};

