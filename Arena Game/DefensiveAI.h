#ifndef DEFENSIVEAI_H_
#define DEFENSIVEAI_H_

#include "AI.h"
#include "Enemy.h"
#include "PausableClock.h"

class DefensiveAI :
	public AI
{
public:
	 DefensiveAI (void) ;
	~DefensiveAI (void) ;

	virtual void computeMove(Enemy& enemy) ;

private:
	PausableClock pClock        ;
	sf::Time      turnRate      ;
	sf::Vector2f  direction     ;
	int           currentAngle  ;
	int           rotatingAngle ;
	int           oppositeAngle ;

	DamagingEntity *damagingEntityPtr;

	//simple AI movement
	sf::Vector2f currentEnemyToTarget;
};
#endif
