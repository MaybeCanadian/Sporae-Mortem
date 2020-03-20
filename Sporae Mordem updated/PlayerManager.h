#pragma once
#include "ObjectManager.h"
#include "Player.h"

class Player;
class PlayerManager
{
private:
	std::vector<Player*> p_vPlayers;
	int numPlayers;
	int playerID;

private:
	void loadTextures();

public:
	PlayerManager();
	bool initManager();
	void clean();
	void addPlayer(int x, int y);
	void removePlayer(int i);
	void clearPlayers();
	void update();
	void render();
	Player* getPlayers(int i);
	int getNumPlayers();
	~PlayerManager();
};

