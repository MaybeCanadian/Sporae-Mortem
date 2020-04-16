#pragma once
#include"engine.h"
#include "button.h"

class button;
class UIManager
{
private:
	UIManager();
	std::vector<button*> ui_vButtons;
	int buttonTextureID[5];
	int backgroundID[4];

private:
	void renderButtons();

public:
	static UIManager& getInstance();
	bool initManager();
	void renderPAUSE(); //renders ui used in pause screen
	void rednerMENU(); //renders ui used in menu screen
	void renderGAME(); //renders ui used in game screen
	void renderLOSE(); //renders the lose screen
	void renderWIN();
	void clean();
	void update();
	void addButton(int x, int y, int w, int h, int type); //0 is pause, 1 is resume, 2 is play, 3 is exit, 4 is menu
	void clearButtons();
	~UIManager();
};

