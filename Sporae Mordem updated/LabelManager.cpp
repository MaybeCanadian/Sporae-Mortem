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
		SDL_Color blue = { 0, 0, 255, 255 };
		labels.push_back(new Label("Press W to move upward.", "Consolas", 20, blue, { 400, 40 }));
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
