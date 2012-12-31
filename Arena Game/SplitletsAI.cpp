#include "SplitletsAI.h"


SplitletsAI::SplitletsAI(void)
{
	type = SPLITLETS;
	currentAngle = 0 ;
}


SplitletsAI::~SplitletsAI(void)
{
}

void SplitletsAI::computeMove(Enemy& enemy)
{
	direction     = VectorFuncs::getDirection(enemy.getPos(),enemy.getTarget()->getPos()) ;
	direction     = VectorFuncs::normalise(direction);
	speed         = VectorFuncs::mult       (direction,sf::Vector2f(3,3))                ;
	enemy.setRotation(-currentAngle)                                                     ;
	enemy.move(speed)                                                                    ;
	currentAngle+=5;
}
