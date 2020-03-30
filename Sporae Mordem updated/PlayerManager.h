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
	int walkID;

private:
	void loadAssets();

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
	void setPlayerPositions(int x, int y); //sets the players to a certain x and y
	~PlayerManager();
};

