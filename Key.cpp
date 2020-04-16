#include "Key.h"

Key::Key(int x, int y, int type, int id)
{
	pos = { x, y, 20, 20 };
	textureID = id;
}

void Key::update()
{
	for (int i = 0; i < ObjectManager::getInstance().getPlayerManager()->getNumPlayers(); i++)
	{
		if (UTIL::AABBcollide(&pos, ObjectManager::getInstance().getPlayerManager()->getPlayers(i)->getRect()))
		{
			std::cout << "got key.\n";
			ObjectManager::getInstance().getPlayerManager()->getPlayers(i)->setHasKey(true);
			LevelStateManager::getInstance().setHasKeyCurrent(false);
			m_active = false;
		}
	}
}

void Key::render()
{
	if (engine::getInstance().getMode() == 0)
	{
		TextureManager::getInstance().Draw(textureID, NULL, &pos);
	}
	else if (engine::getInstance().getMode() == 1)
	{
		TextureManager::getInstance().Draw(0, NULL, &pos);
	}
}

bool Key::getActive()
{
	return m_active;
}

Key::~Key()
{
}
