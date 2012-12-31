#include "DefensiveAI.h"


DefensiveAI::DefensiveAI(void)
{
	type = DEFENSIVE;
	currentAngle  = 0 ;
	rotatingAngle = 0 ;
	turnRate = sf::milliseconds(1);
}


DefensiveAI::~DefensiveAI(void)
{
}

void DefensiveAI::computeMove(Enemy& enemy)
{	
	direction     = VectorFuncs::getDirection (enemy.getPos(),enemy.getTarget()->getPos()) ;
	rotatingAngle = (int)VectorFuncs::getAngle(direction)                             ;
	enemy.setRotation((float)-rotatingAngle) ;        

	for(unsigned int i = 0 ; i < enemy.getDamagingList()->size() ; i++)
	{
		damagingEntityPtr = dynamic_cast<DamagingEntity*>(enemy.getDamagingList()->at(i));
		if(damagingEntityPtr != NULL && (damagingEntityPtr->getSubType() == DamagingEntity::PROJECTILE))
		{
			if(abs(VectorFuncs::distance(damagingEntityPtr->getPos(),enemy.getPos()) < 100))
			{
				damagingEntityPtr->setPos(damagingEntityPtr->getPos() - VectorFuncs::mult(sf::Vector2f(6,6), VectorFuncs::normalise(VectorFuncs::getDirection(damagingEntityPtr->getPos(),enemy.getPos()))));
			}
		}
	}

	//simple AI movement
	currentEnemyToTarget = enemy.getTarget()->getPos() - enemy.getPos();
	currentEnemyToTarget = VectorFuncs::normalise(currentEnemyToTarget);

	currentEnemyToTarget.x = currentEnemyToTarget.x *2;
	currentEnemyToTarget.y = currentEnemyToTarget.y *2;
	enemy.move(currentEnemyToTarget);
}