#include "LoadZone.h"



LoadZone::LoadZone(int x, int y, int in)
{
	z_dst = { x, y, 30, 30 };
	nextZone = in;
}

LoadZone::~LoadZone()
{
}

int LoadZone::getNext()
{
	return nextZone;
}
