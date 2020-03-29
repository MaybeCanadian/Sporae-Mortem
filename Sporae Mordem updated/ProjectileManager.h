#pragma once
#include "ObjectManager.h"
#include "Rock.h"

class Rock;
class ProjectileManager
{
private:
	std::vector<Rock*> r_vRocks;
	bool updateRock;
	int rocktimer;
public:
	ProjectileManager();
	bool initManager();
	void clean();
	void addRock(int x, int y, double rotation);
	void update();
	void render();
	~ProjectileManager();
};

