#include "UIManager.h"

UIManager::UIManager()
{
}

void UIManager::renderButtons()
{
	if (!ui_vButtons.empty())
	{
		for (int i = 0; i < (int)ui_vButtons.size(); i++)
			ui_vButtons[i]->render();
	}
}

UIManager & UIManager::getInstance()
{
	static UIManager instance;
	return instance;
}

bool UIManager::initManager()
{
	buttonTextureID[0] = TextureManager::getInstance().addTexture("Image/pause.png"); //add file name
	buttonTextureID[1] = TextureManager::getInstance().addTexture("Image/resume.png"); //add file name
	buttonTextureID[2] = TextureManager::getInstance().addTexture("Image/Play.png"); //add file name
	buttonTextureID[3] = TextureManager::getInstance().addTexture("Image/exit.png"); //add file name
	buttonTextureID[4] = TextureManager::getInstance().addTexture("Image/menu.png"); //add file name
	backgroundID[0] = TextureManager::getInstance().addTexture("Image/startscreen.png");
	backgroundID[1] = TextureManager::getInstance().addTexture("Image/floor.png");
	backgroundID[2] = TextureManager::getInstance().addTexture("Image/endgame.png");
	backgroundID[3] = TextureManager::getInstance().addTexture("Image/winscreen.png");
	std::cout << "uimanager init.\n";
	return true;
}

void UIManager::renderPAUSE()
{
	renderButtons();
}

void UIManager::rednerMENU()
{
	if (engine::getInstance().getMode() == 0)
	{
		TextureManager::getInstance().Draw(backgroundID[0], NULL, NULL);
	}
	else if (engine::getInstance().getMode() == 1)
	{
		TextureManager::getInstance().Draw(0, NULL, NULL);
	}
	renderButtons();
}

void UIManager::renderGAME()
{
	if (engine::getInstance().getMode() == 0)
	{
		TextureManager::getInstance().Draw(backgroundID[1], NULL, NULL);
	}
	else if (engine::getInstance().getMode() == 1)
	{
		TextureManager::getInstance().Draw(0, NULL, NULL);
	}
}

void UIManager::renderLOSE()
{
	if (engine::getInstance().getMode() == 0)
	{
		TextureManager::getInstance().Draw(backgroundID[2], NULL, NULL);
	}
	else if (engine::getInstance().getMode() == 1)
	{
		TextureManager::getInstance().Draw(0, NULL, NULL);
	}
	renderButtons();
}

void UIManager::renderWIN()
{
	if (engine::getInstance().getMode() == 0)
	{
		TextureManager::getInstance().Draw(backgroundID[3], NULL, NULL);
	}
	else if (engine::getInstance().getMode() == 1)
	{
		TextureManager::getInstance().Draw(0, NULL, NULL);
	}
}

void UIManager::clean()
{
	//nothing to clean yet
	std::cout << "uimanager clean.\n";
}

void UIManager::update()
{
	if (!ui_vButtons.empty())
	{
		for (int i = 0; i < (int)ui_vButtons.size(); i++)
		{
			ui_vButtons[i]->update();
		}
	}
}

void UIManager::addButton(int x, int y, int w, int h, int type)
{
	switch (type)
	{
	case 0:
		ui_vButtons.push_back(new pauseButton(x, y, w, h, buttonTextureID[type]));
		break;
	case 1:
		ui_vButtons.push_back(new ResumeButton(x, y, w, h, buttonTextureID[type]));
		break;
	case 2:
		ui_vButtons.push_back(new PlayButton(x, y, w, h, buttonTextureID[type]));
		break;
	case 3:
		ui_vButtons.push_back(new ExitButton(x, y, w, h, buttonTextureID[type]));
		break;
	case 4:
		ui_vButtons.push_back(new menuButton(x, y, w, h, buttonTextureID[type]));
		break;
	}
}

void UIManager::clearButtons()
{
	if (!ui_vButtons.empty())
	{
		ui_vButtons.clear();
		ui_vButtons.shrink_to_fit();
	}
}

UIManager::~UIManager()
{
}
