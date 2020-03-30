#pragma once
#include "Pathfinder.h"

class node
{
private:
	SDL_Point pos;
	SDL_Rect dst;
	node* parent;
	node* neighbour[4];
	int cost;
	int dist;

	bool isStart;
	bool isGoal;
	bool visited;
	bool passable;

public:
	node(int x, int y, bool pass);
	void setNeighbour(int side, node* input);
	node* getNeighbour(int side);
	bool getpassable();
	void setBoolData(int type, bool input); //0 is start, 1 is goal, 2 is vivited
	bool getBoolData(int type); //0 is start, 1 is goal, 2 is visited
	void setParent(node* par);
	node* getParent();
	void setDistance(int input);
	int getDistance();
	int getCost();
	void render();
	SDL_Point* getPoint();
	void reset();
	~node();
};

