#pragma once
#include <SDL.h>
#include <math.h>
#include <vector>
#include <algorithm>

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

	static bool LineLineCollide(SDL_Point line1Start, SDL_Point line1End, SDL_Point line2Start, SDL_Point line2End)
	{
		int x1 = line1Start.x;
		int x2 = line1End.x;
		int x3 = line2Start.x;
		int x4 = line2End.x;
		int y1 = line1Start.y;
		int y2 = line1End.y;
		int y3 = line2Start.y;
		int y4 = line2End.y;

		// calculate the distance to intersection point
		float uA = ((x4 - x3) * (y1 - y3) - (y4 - y3) * (x1 - x3)) / ((y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1)) * 1.0;
		float uB = ((x2 - x1) * (y1 - y3) - (y2 - y1) * (x1 - x3)) / ((y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1)) * 1.0;

		// if uA and uB are between 0-1, lines are colliding
		if (uA >= 0 && uA <= 1 && uB >= 0 && uB <= 1)
		{
			return true;
		}

		return false;
	}

	static bool lineRectCheck(SDL_Point line1Start, SDL_Point line1End, SDL_Point recStart, float recWidth, float recHeight)
	{
		int x1 = line1Start.x;
		int x2 = line1End.x;
		int y1 = line1Start.y;
		int y2 = line1End.y;
		int rx = recStart.x;
		int ry = recStart.y;
		int rw = recWidth;
		int rh = recHeight;


		// check if the line has hit any of the rectangle's sides
		// uses the Line/Line function below
		SDL_Point vec1 = { x1, y1 };
		SDL_Point vec2 = { x2, y2 };
		SDL_Point vec3 = { rx, ry };
		SDL_Point vec4 = { rx, ry + rh };
		bool left = LineLineCollide(vec1, vec2, vec3, vec4);
		vec1 = { x1, y1 }; vec2 = { x2, y2 }; vec3 = { rx + rw, ry }; vec4 = { rx + rw, ry + rh };
		bool right = LineLineCollide(vec1, vec2, vec3, vec4);
		vec1 = { x1, y1 }; vec2 = { x2, y2 }; vec3 = { rx, ry }; vec4 = { rx + rw, ry };
		bool top = LineLineCollide(vec1, vec2, vec3, vec4);
		vec1 = { x1, y1 }; vec2 = { x2, y2 }; vec3 = { rx, ry + rh }; vec4 = { rx + rw, ry + rh };
		bool bottom = LineLineCollide(vec1, vec2, vec3, vec4);

		// if ANY of the above are true, the line
		// has hit the rectangle
		if (left || right || top || bottom) {
			return true;
		}
		return false;
	}

	static double Trunacate(double value1, double value2)
	{
		if (value1 < value2)
			return value1;
		else
			return value2;
	}

	static double Trunacate(int value1, double value2)
	{
		if (value1 < value2)
			return value1;
		else
			return value2;
	}

	static double Trunacate(double value1, int value2)
	{
		if (value1 < value2)
			return value1;
		else
			return value2;
	}

	static int Trunacate(int value1, int value2) //returns the lower value
	{
		if (value1 < value2)
			return value1;
		else
			return value2;
	}

	static int limit(int value, int limiter)
	{
		if (value < limiter)
			return limiter;
		else
			return value;
	}


	static bool linePointColide(SDL_Point* point, SDL_Point* lineStart, SDL_Point* lineEnd, int buffer)
	{
		int LineDistance = sqrt(pow(lineEnd->x - lineStart->x, 2) + pow(lineEnd->y - lineStart->y, 2));
		int PointDistance1 = sqrt(pow(lineStart->x - point->x, 2) + pow(lineStart->y - point->y, 2));
		int PointDistance2 = sqrt(pow(lineEnd->x - point->x, 2) + pow(lineEnd->y - point->y, 2));

		if (PointDistance1 + PointDistance2 >= LineDistance - buffer && PointDistance1 + PointDistance2 <= LineDistance + buffer)
		{
			return true;
		}
		else return false;
	}
};
