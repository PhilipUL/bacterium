#ifndef SIMPLEAI_H_
#define SIMPLEAI_H_

#include "AI.h"
#include "Enemy.h"
#include "SFML\Graphics.hpp"

class Enemy;

class SimpleAI : public AI
{
public:
	SimpleAI();
	~SimpleAI();

	void computeMove(Enemy &enemy);

private:
	sf::Vector2f currentEnemyToTarget;
	int rotatingAngle;
};

#endif