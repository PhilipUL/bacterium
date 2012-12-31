
#include "SplitterAI.h"

SplitterAI::SplitterAI(void)
{
	type = SPLIT;
}


SplitterAI::~SplitterAI(void)
{
}

void SplitterAI::computeMove(Enemy& enemy)
{   
	direction     = VectorFuncs::getDirection(enemy.getPos(),enemy.getTarget()->getPos());
	direction     = VectorFuncs::normalise(direction)                                    ;
	currentAngle  = (float)VectorFuncs::getAngle(direction);
	speed         = VectorFuncs::mult       (direction,sf::Vector2f(3,3))                ;
	enemy.setRotation(-currentAngle)                                                     ;
	enemy.move(speed)                                                                    ;
}
