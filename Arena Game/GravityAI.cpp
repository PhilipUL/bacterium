#include "GravityAI.h"

GravityAI::GravityAI(void)
{
	type = GRAVITY;
	if(rand() % 2 == 1)
		direction.x = 1;
	else
		direction.x = -1;
	if(rand() % 2 == 1)
		direction.y = 1;
	else
		direction.y = -1;
}


GravityAI::~GravityAI(void)
{
}

void GravityAI::computeMove(Enemy& enemy)
{
	for(unsigned int i = 0 ; i < enemy.getDamagingList()->size() ; i++)
	{
		damagingEntityPtr = dynamic_cast<DamagingEntity*>(enemy.getDamagingList()->at(i));
		if(damagingEntityPtr != NULL && (damagingEntityPtr->getSubType() == DamagingEntity::PROJECTILE || damagingEntityPtr->getSubType() == DamagingEntity::TRAP))
		{
			if(abs(VectorFuncs::distance(damagingEntityPtr->getPos(),enemy.getPos()) < 200))
			{
				damagingEntityPtr->setPos(damagingEntityPtr->getPos() + VectorFuncs::mult(sf::Vector2f(4,4), VectorFuncs::normalise(VectorFuncs::getDirection(damagingEntityPtr->getPos(),enemy.getPos()))));
			}
		}
	}

	//simple AI movement
	currentEnemyToTarget = enemy.getTarget()->getPos() - enemy.getPos();
	currentEnemyToTarget = VectorFuncs::normalise(currentEnemyToTarget);

	currentEnemyToTarget.x = currentEnemyToTarget.x *2;
	currentEnemyToTarget.y = currentEnemyToTarget.y *2;
	enemy.move(currentEnemyToTarget);

	rotatingAngle = (int)VectorFuncs::getAngle(currentEnemyToTarget);
	enemy.setRotation((float)-rotatingAngle);
}
