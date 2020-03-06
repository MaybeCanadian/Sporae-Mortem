#pragma once
#include "button.h"
class ResumeButton :
	public button
{
public:
	void onClick();
	ResumeButton(int x, int y, int w, int h, int id);
	~ResumeButton();
};

