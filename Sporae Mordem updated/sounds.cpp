#include "sounds.h"

const double sounds::getRadius()
{
	return radius;
}

const SDL_Point * sounds::getPos()
{
	return &position;
}

sounds::sounds(int x, int y, double rad, int dur)
{
	position.x = x;
	position.y = y;
	radius = rad;
	s_active = true;
	time = 0;
}

void sounds::update()
{
	time++;
	if (time > duration)
		s_active = false;
}

bool sounds::getActive()
{
	return s_active;
}


sounds::~sounds()
{
}
