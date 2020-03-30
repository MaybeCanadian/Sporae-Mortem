#include "PickupManager.h"



PickupManager::PickupManager()
{
}

bool PickupManager::initManager()
{
	KeyTextureID = TextureManager::getInstance().addTexture("Image/key.png");
	std::cout << "PickupManager init.\n";
	return true;
}

void PickupManager::clean()
{
	clearKeys();
	std::cout << "PickupManager Cleaned.\n";
}

void PickupManager::addKey(int x, int y, int type)
{
	keys.push_back(new Key(x, y, type, KeyTextureID));
}

void PickupManager::clearKeys()
{
	if (!keys.empty())
	{
		for (int i = 0; i < (int)keys.size(); i++)
		{
			delete keys[i];
			keys[i] = nullptr;
		}
		keys.clear();
		keys.shrink_to_fit();
	}
}

void PickupManager::update()
{
	if (!keys.empty())
	{
		for (int i = 0; i < (int)keys.size(); i++)
		{
			keys[i]->update();
		}

		for (int i = 0; i < (int)keys.size(); i++)
		{
			if (keys[i]->getActive() == false)
			{
				delete keys[i];
				keys[i] = nullptr;
			}
		}

		for (int i = 0; i < (int)keys.size(); i++)
		{
			if (keys[i] == nullptr)
			{
				keys.erase(keys.begin() + i);
			}
		}
	}
}

void PickupManager::render()
{
	if (!keys.empty())
	{
		for (int i = 0; i < (int)keys.size(); i++)
		{
			keys[i]->render();
		}
	}
}

PickupManager::~PickupManager()
{
}
