#pragma once
#include "UIManager.h"

class button
{
protected:
	SDL_Rect b_dst,
		b_src = {0,0,400,100};
	int textueID;
	enum state { STATE_UP, STATE_OVER, STATE_DOWN } b_state;

protected:
	virtual void onClick() = 0;
public:
	void setTexture(int id);
	void update();
	void render();
	button();
	~button();
};

#include "pauseButton.h"
#include "PlayButton.h"
#include "ResumeButton.h"
#include "ExitButton.h"
#include "menuButton.h"

