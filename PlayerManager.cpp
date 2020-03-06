#include "PlayerManager.h"



PlayerManager::PlayerManager()
{
}

bool PlayerManager::initManager()
{
	//nothing to init yet
	std::cout << "playerManager init.\n";
	return true;
}

void PlayerManager::clean()
{
	p_vPlayers.clear();
	p_vPlayers.shrink_to_fit();
	std::cout << "playerManager clean.\n";
}

void PlayerManager::addPlayer(int x, int y)
{
	p_vPlayers.push_back(new Player(x, y, (int)p_vPlayers.size()));
}

void PlayerManager::removePlayer(int i)
{
	delete p_vPlayers[i];
	p_vPlayers[i] = nullptr;
	p_vPlayers.erase(p_vPlayers.begin() + i);
}

void PlayerManager::clearPlayers()
{
	if (!p_vPlayers.empty())
	{
		p_vPlayers.clear();
		p_vPlayers.shrink_to_fit();
	}
}

void PlayerManager::update()
{
	if (!p_vPlayers.empty())
	{
		for (int i = 0; i < (int)p_vPlayers.size(); i++)
		{
			p_vPlayers[i]->update();
		}
	}
}

void PlayerManager::render()
{
	if (!p_vPlayers.empty())
	{
		for (int i = 0; i < (int)p_vPlayers.size(); i++)
		{
			p_vPlayers[i]->render();
		}
	}
}


PlayerManager::~PlayerManager()
{
}
