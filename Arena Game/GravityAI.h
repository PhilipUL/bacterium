#ifndef GRAVITYAI_H_
#define GRAVITYAI_H_

#include "AI.h"
#include "Enemy.h"
#include "DamagingEntity.h"

class GravityAI : public AI
{
public:
	GravityAI(void);
	~GravityAI(void);

	virtual void computeMove(Enemy& enemy);

private:
	sf::Vector2f direction;

	DamagingEntity *damagingEntityPtr;

	sf::Vector2f currentEnemyToTarget;
	int rotatingAngle;
};
#endif
