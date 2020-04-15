#include "node.h"

node::node(int x, int y, bool pass)
{
	pos = { x , y};
	passable = pass;
	for (int i = 0; i < 4; i++)
		neighbour[i] = nullptr;
	cost = 5;
	dist = 10000;
	dst = { x, y, GRID, GRID };
	isStart = false;
	isGoal = false;
	visited = false;
}

void node::setNeighbour(int side, node * input)
{
	neighbour[side] = input;
}

node * node::getNeighbour(int side)
{
	return neighbour[side];
}

bool node::getpassable()
{
	return passable;
}

void node::setBoolData(int type, bool input)
{
	if (type == 0)
		isStart = input;
	else if (type == 1)
		isGoal = input;
	else if (type == 2)
		visited = input;
}

bool node::getBoolData(int type)
{
	if (type == 0)
		return isStart;
	else if (type == 1)
		return isGoal;
	else if (type == 2)
		return visited;
}

void node::setParent(node * par)
{
	parent = par;
}

node * node::getParent()
{
	return parent;
}

void node::setDistance(int input)
{
	dist = input;
}

int node::getDistance()
{
	return dist;
}

int node::getCost()
{
	return cost;
}

void node::render()
{
	TextureManager::getInstance().SetDrawColor(255, 255, 255, 255);
	if (neighbour[0] != nullptr)
	{
		TextureManager::getInstance().SetDrawColor(255, 255, 255, 255);
		SDL_Rect up = { dst.x, dst.y, GRID / 2, GRID / 2 };
		TextureManager::getInstance().FillRect(&up);
	}
	if (neighbour[1] != nullptr)
	{
		TextureManager::getInstance().SetDrawColor(255, 0, 255, 255);
		SDL_Rect right = { dst.x + GRID / 2 , dst.y, GRID / 2, GRID / 2 };
		TextureManager::getInstance().FillRect(&right);
	}
	if (neighbour[2] != nullptr)
	{
		TextureManager::getInstance().SetDrawColor(0, 255, 255, 255);
		SDL_Rect down = { dst.x + GRID / 2, dst.y + GRID / 2, GRID / 2, GRID / 2 };
		TextureManager::getInstance().FillRect(&down);
	}
	if (neighbour[3] != nullptr)
	{
		TextureManager::getInstance().SetDrawColor(255, 255, 0, 255);
		SDL_Rect left = { dst.x, dst.y + GRID / 2, GRID / 2, GRID / 2 };
		TextureManager::getInstance().FillRect(&left);
	}
}

SDL_Point * node::getPoint()
{
	return &pos;
}

void node::reset()
{
	visited = false;
	dist = 1000;
	parent = nullptr;
	isGoal = false;
	isStart = false;
}

node::~node()
{
}
