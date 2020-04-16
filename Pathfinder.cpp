#include "Pathfinder.h"

void Pathfinder::Checkneighbours(node * current)
{
	//check all neighbours
	//start up
	if (current->getNeighbour(0) != nullptr)
	{
		if (!current->getNeighbour(0)->getBoolData(2))
		{
			if (current->getNeighbour(0)->getDistance() > current->getDistance() + current->getNeighbour(0)->getCost())
			{
				current->getNeighbour(0)->setDistance(current->getDistance() + current->getNeighbour(0)->getCost());
				current->getNeighbour(0)->setParent(current);
			}
		}
	}

	//check right
	if (current->getNeighbour(1) != nullptr)
	{
		if (!current->getNeighbour(1)->getBoolData(2))
		{
			if (current->getNeighbour(1)->getDistance() > current->getDistance() + current->getNeighbour(1)->getCost())
			{
				current->getNeighbour(1)->setDistance(current->getDistance() + current->getNeighbour(1)->getCost());
				current->getNeighbour(1)->setParent(current);
			}
		}
	}

	//check down
	if (current->getNeighbour(2) != nullptr)
	{
		if (!current->getNeighbour(2)->getBoolData(2))
		{
			if (current->getNeighbour(2)->getDistance() > current->getDistance() + current->getNeighbour(2)->getCost())
			{
				current->getNeighbour(2)->setDistance(current->getDistance() + current->getNeighbour(2)->getCost());
				current->getNeighbour(2)->setParent(current);
			}
		}
	}

	//check left
	if (current->getNeighbour(3) != nullptr)
	{
		if (!current->getNeighbour(3)->getBoolData(2))
		{
			if (current->getNeighbour(3)->getDistance() > current->getDistance() + current->getNeighbour(3)->getCost())
			{
				current->getNeighbour(3)->setDistance(current->getDistance() + current->getNeighbour(3)->getCost());
				current->getNeighbour(3)->setParent(current);
			}
		}
	}
}

void Pathfinder::resetnodes()
{
	if (!nodes.empty())
	{
		for (int i = 0; i < (int)nodes.size(); i++)
		{
			nodes[i]->reset();
		}
	}
}

void Pathfinder::loadNeighbours()
{
	std::cout << "number of rows: " << rownum << std::endl;
	std::cout << "number of columns " << colnum << std::endl;
	if (!nodes.empty())
	{
		for (int i = 0; i < (int)nodes.size(); i++)
		{
			if (nodes[i]->getpassable() == true)
			{
				//load up
				if (i >= colnum)
				{
					if (nodes[i - colnum]->getpassable() == true)
					{
						nodes[i]->setNeighbour(0, nodes[i - colnum]);
					}
				}

				//load right
				if ((i + 1) % colnum != 0)
				{
					if (nodes[i + 1]->getpassable() == true)
					{
						nodes[i]->setNeighbour(1, nodes[i + 1]);
					}
				}

				//load down
				if (i < (colnum * rownum - colnum))
				{
					if (nodes[i + colnum]->getpassable() == true)
					{
						nodes[i]->setNeighbour(2, nodes[i + colnum]);
					}
				}

				//load left
				if (i % colnum != 0)
				{
					if (nodes[i - 1]->getpassable() == true)
					{
						nodes[i]->setNeighbour(3, nodes[i - 1]);
					}
				}
			}
		}
	}
	std::cout << "all neighbours loaded.\n";
	std::cout << (int)nodes.size() << std::endl;
}

void Pathfinder::addNode(int x, int y, bool passable)
{
	nodes.push_back(new node(x, y, passable));
}

void Pathfinder::setData(int x, int y)
{
	rownum = x;
	colnum = y;
}

bool Pathfinder::findPath(std::vector<SDL_Point>* path, int xStart, int yStart, int xGoal, int yGoal)
{
	std::vector<node*> unvisited;

	for (int i = 0; i < (int)nodes.size(); i++)
	{
		unvisited.push_back(nodes[i]);
	}
	int startpoint = (int)(xStart / GRID) + (int)((yStart / GRID) * colnum);
	int endpoint = (int)(xGoal / GRID) + (int)((yGoal / GRID) * colnum);
	int current = -1;
	int lowestDist = 1000;

	std::cout << "the start point is " << startpoint << std::endl;
	std::cout << "The endpoint is " << endpoint << std::endl;

	nodes[startpoint]->setBoolData(0, true); //finding the nodes that we start and end at
	nodes[startpoint]->setDistance(0);
	nodes[endpoint]->setBoolData(1, true);

	bool atEnd = false; //flag to hold the while loop

	if (startpoint == endpoint)
	{
		path->clear();
		atEnd == true;
		std::cout << "at endpoint already" << std::endl;
		path->insert(path->begin(), *(nodes[endpoint]->getPoint()));
		return true;
	}
	

	while (!atEnd)
	{
		current = -1;
		lowestDist = 999;
		for (int i = 0; i < (int)unvisited.size(); i++)
		{
			if (unvisited[i]->getDistance() < lowestDist)
			{
				lowestDist = unvisited[i]->getDistance();
				current = i;
			}
		}

		if (current == -1)
		{
			std::cout << "no path found.\n";
			return false;
		}

		if (unvisited[current]->getBoolData(1))
		{
			atEnd = true;
		}
		else
		{
			Checkneighbours(unvisited[current]);
			unvisited[current]->setBoolData(2, true);
			unvisited.erase(unvisited.begin() + current);
		}
	}

	bool atStart = false;

	node* current_node = unvisited[current];
	
	path->clear();

	while (current_node->getBoolData(0) == false)
	{
		SDL_Point buffer = { current_node->getPoint()->x + GRID / 2 , current_node->getPoint()->y + GRID / 2 };
		path->insert((path->begin()), buffer);
		current_node = current_node->getParent();
	}


	std::cout << "path size in pathfinder is " << path->size() << std::endl;
	std::cout << "path found\n";

	resetnodes();
	return true;
}

void Pathfinder::clearNodes()
{
	if (!nodes.empty())
	{
		for (int i = 0; i < (int)nodes.size(); i++)
		{
			delete nodes[i];
			nodes[i] = nullptr;
		}

		nodes.clear();
		nodes.shrink_to_fit();
	}
}

bool Pathfinder::initManager()
{
	rownum = 0;
	colnum = 0;
	std::cout << "Pathfinder init.\n";
	return true;
}

void Pathfinder::clean()
{
	clearNodes();
	std::cout << "Pathfinder cleaned.\n";
}

int Pathfinder::getNodeNum()
{
	return nodes.size();
}

node * Pathfinder::getNode(int i)
{
	return nodes[i];
}

void Pathfinder::render()
{
	if (!nodes.empty())
	{
		for (int i = 0; i < (int)nodes.size(); i++ )
		{
			nodes[i]->render();
		}
	}
}

Pathfinder::Pathfinder()
{
}


Pathfinder::~Pathfinder()
{
}
