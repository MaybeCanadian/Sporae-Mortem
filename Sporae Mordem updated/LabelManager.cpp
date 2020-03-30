#include "LabelManager.h"

LabelManager::LabelManager()
{
}

LabelManager& LabelManager::getInstance()
{
	static LabelManager instance;
	return instance;
}

LabelManager::~LabelManager()
{
}

bool LabelManager::initManager()
{
	active = true;
	SDL_Color white = { 255, 255, 255, 255 };
	labels.push_back(new Label("Press W to move upward.", "Consolas", 25, white, { 35, 400 }));
	labels.push_back(new Label("Press S to move downward.", "Consolas", 25, white, { 35, 425 }));
	labels.push_back(new Label("Press A to move leftward.", "Consolas", 25, white, { 35, 450 }));
	labels.push_back(new Label("Press D to move rightward.", "Consolas", 25, white, { 35, 475 }));
	labels.push_back(new Label("LeftClick to throw stone.", "Consolas", 25, white, { 35, 500 }));
	labels.push_back(new Label("RightClick to sneak.", "Consolas", 25, white, { 35, 525 }));
	std::cout << "LabelManager init.\n";
	return true;
}

void LabelManager::clean()
{
	if (!labels.empty())
	{
		for (int i = 0; i < (int)labels.size(); i++)
		{
			delete labels[i];
			labels[i] = nullptr;
		}
		labels.clear();
		labels.shrink_to_fit();
	}
}

void LabelManager::render()
{
	if (!labels.empty())
	{
		for (int i = 0; i < (int)labels.size(); i++)
		{
			labels[i]->render();
		}
	}
}

void LabelManager::update()
{
}

void LabelManager::setActive(bool flag)
{
	active = flag;
}

bool LabelManager::getActive()
{
	return active;
}
