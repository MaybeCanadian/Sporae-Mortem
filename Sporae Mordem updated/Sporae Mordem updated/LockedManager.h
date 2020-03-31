#pragma once
#include "ObjectManager.h"
#include "Door.h"

class Door;
class LockedManager
{
private:
	std::vector<Door*> doors;
	int DoorTextureID;
public:
	LockedManager();
	bool initManager();
	void clean();
	void update();
	void render();
	void clearDoors();
	void addDoor(int x, int y,int zone, int type);
	bool checkNearLocked(SDL_Rect* input, bool key, int type); //returns true if colliding
	~LockedManager();
};

