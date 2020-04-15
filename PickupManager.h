#pragma once
#include "ObjectManager.h"
#include "Key.h"

class Key;
class PickupManager
{
private:
	std::vector<Key*> keys;
	int KeyTextureID;

public:
	PickupManager();
	bool initManager();
	void clean();
	void addKey(int x, int y, int type);
	void clearKeys();
	void update();
	void render();
	~PickupManager();
};

