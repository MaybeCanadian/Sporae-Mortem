#include "PlayerManager.h"



void PlayerManager::loadTextures()
{
	playerID = TextureManager::getInstance().addTexture("prisoner.png");
}

PlayerManager::PlayerManager()
{
}

bool PlayerManager::initManager()
{
	//nothing to init yet
	loadTextures();
	numPlayers = 0;
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
	p_vPlayers.push_back(new Player(x, y, (int)p_vPlayers.size(), playerID));
	numPlayers++;
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
		numPlayers = 0;
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

Player * PlayerManager::getPlayers(int i)
{
	return p_vPlayers[i];
}

int PlayerManager::getNumPlayers()
{
	return numPlayers;
}

void PlayerManager::setPlayerPositions(int x, int y)
{
	if (!p_vPlayers.empty())
	{
		for (int i = 0; i < (int)p_vPlayers.size(); i++)
		{
			p_vPlayers[i]->setPos(x, y);
		}
	}
}


PlayerManager::~PlayerManager()
{
}
