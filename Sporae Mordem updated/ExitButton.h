#pragma once
#include "button.h"
class ExitButton :
	public button
{
public:
	void onClick();
	ExitButton(int x, int y, int w, int h, int id);
	~ExitButton();
};

