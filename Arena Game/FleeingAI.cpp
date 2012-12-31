#include "FleeingAI.h"


FleeingAI::FleeingAI()
{
	srand((unsigned int)time(NULL))			 ;
	changeDirection = sf::milliseconds(2000) ;
	computeDirection()                       ;
	type = FLEEING;
}

FleeingAI::~FleeingAI()
{
}

void FleeingAI::computeMove(Enemy &enemy)
{
	if(pClock.getElapsedTime() >= changeDirection)
	{
		computeDirection();
		pClock.restart();
	}

	enemy.move(direction);
}

void FleeingAI::computeDirection()
{
	up   = rand() % 2                                          ;
	left = rand() % 2                                          ;
    x    = (float)(rand() % 5)                                 ;
	y    = (float)(rand() % 5)                                 ;

	if(up != 0)
		y = -y;
	if(left != 0)
		x = -x;

	direction = sf::Vector2f(x,y)                              ; 
	direction = VectorFuncs::normalise(direction)              ;
	direction = VectorFuncs::mult(direction,sf::Vector2f(3,3)) ;
}
