#pragma once
#include "ObjectManager.h"
#include "node.h"

class node;
class Pathfinder
{
private:
	std::vector<node*> nodes;
	int rownum, colnum;

private:
	void Checkneighbours(node* current);
	void resetnodes();
public:
	void loadNeighbours(); //loads all neighbours to nodes
	void addNode(int x, int y, bool passable); //adds a node
	void setData(int x, int y); //sets rows to x, sets col to y

	bool findPath(std::vector<SDL_Point>* path, int xStart, int yStart, int xGoal, int yGoal);

	void clearNodes(); //clears all the nodes
	bool initManager(); //inits the manager
	void clean(); //cleans the manager


	void render();
	Pathfinder();
	~Pathfinder();
};

