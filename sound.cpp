#include "sound.h"

sound::sound(int x, int y, double radius, int duration)
{
	this->x = x;
	this->y = y;
	this->radius = radius;
}
sound::~sound()
{
}

int const sound::getSoundX()
{
	return x;
}

int const sound::getSoundY()
{
	return y;
}

double const sound::getSoundRadius()
{
	return radius;
}
