#include "Rock.h"



Rock::Rock(double rotation, SDL_Rect player)
{
	unitVecX = cos(rotation);
	unitVecY = sin(rotation);
	speed = 5;
	m_dst.x = player.x;
	m_dst.y = player.y;
}

Rock::~Rock()
{
}

void Rock::update()
{
	m_dst.x = m_dst.x + speed * unitVecX;
	m_dst.y = m_dst.y + speed * unitVecY;
}

void Rock::render()
{

}
