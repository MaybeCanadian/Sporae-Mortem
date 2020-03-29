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
	backgroundID = TextureManager::getInstance().addTexture("floor.png");
	std::cout << "uimanager init.\n";
	return true;
}

void UIManager::renderPAUSE()
{
	TextureManager::getInstance().SetDrawColor(0, 0, 255, 255);
	TextureManager::getInstance().FillRect(NULL);
	renderButtons();
}

void UIManager::rednerMENU()
{
	TextureManager::getInstance().SetDrawColor(255, 0, 0, 255);
	TextureManager::getInstance().FillRect(NULL);
	renderButtons();
}

void UIManager::renderGAME()
{
	TextureManager::getInstance().Draw(backgroundID, NULL, NULL);
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
