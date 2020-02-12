#pragma once
#include"basic_includes.h"
class sound
{
private:
	int x, y;
	double radius;

public:
	sound(int x, int y, double radius, int duration);
	~sound();
	int const getSoundX();
	int const getSoundY();
	double const getSoundRadius();
};

