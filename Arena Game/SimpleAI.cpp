#include "SimpleAI.h"

SimpleAI::SimpleAI()
{
	type = SIMPLE;
}

void SimpleAI::computeMove(Enemy &enemy)
{
	currentEnemyToTarget = enemy.getTarget()->getPos() - enemy.getPos();
	currentEnemyToTarget = VectorFuncs::normalise(currentEnemyToTarget);

	currentEnemyToTarget.x = currentEnemyToTarget.x *2;
	currentEnemyToTarget.y = currentEnemyToTarget.y *2;
	enemy.move(currentEnemyToTarget);

	rotatingAngle = (int)VectorFuncs::getAngle(currentEnemyToTarget);
	enemy.setRotation((float)-rotatingAngle);
}
