#pragma once
#include <SDL.h>
#include <math.h>

class UTIL //fun things i can use
{
public:
	static double distanceRect(SDL_Rect* rect1, SDL_Rect* rect2) { return (sqrt((pow(rect1->x - rect2->x, 2) + pow(rect1->y - rect2->y, 2)))); } //returns the distance between two rectangles top left corners

	static double distancePoint(SDL_Point* p1, SDL_Point* p2) {	return (sqrt((pow(p1->x - p2->x, 2) + pow(p1->y - p2->y, 2)))); } //returns the distance bewtween two points

	static double distancePoint(SDL_Point* p1, const SDL_Point* p2) { return (sqrt((pow(p1->x - p2->x, 2) + pow(p1->y - p2->y, 2)))); }

	static bool AABBcollide(SDL_Rect * rect1, SDL_Rect * rect2)	//checks if two rectangles are coliding
	{
		if ((rect1->x < rect2->x + rect2->w) && (rect1->x + rect1->w > rect2->x) && (rect1->y < rect2->y + rect2->h) && (rect1->y + rect1->h > rect2->y))
			return true;
		else
			return false;
	}

	static bool CircleCollide(SDL_Point * rect1, double radius1, SDL_Point * rect2, double radius2) //checks if two circles are coliding
	{
		if ((sqrt(pow((rect1->x - rect2->x), 2) + pow((rect1->y - rect2->y), 2))) < (radius1 + radius2))
			return true;
		else
			return false;
	}

	static bool CircleCollide(SDL_Point * rect1, double radius1, const SDL_Point * rect2, const double radius2) //checks if two circles are coliding, overide with const
	{
		if ((sqrt(pow((rect1->x - rect2->x), 2) + pow((rect1->y - rect2->y), 2))) < (radius1 + radius2))
			return true;
		else
			return false;
	}

	static bool PointRectCollide(SDL_Point* p1, SDL_Rect* rect) {
		if (p1->y > (rect->y + rect->h) || p1->y < rect->y || p1->x >(rect->x + rect->w) || p1->x < (rect->x))
			return false;
		else
			return true;
	}

	static double Rotation(SDL_Point* p1, SDL_Point* p2) //player p2, mouse p1, in degrees
	{
		return (atan2((p1->y - p2->y) , (p1->x - p2->x)));
	}
};
