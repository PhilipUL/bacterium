#ifndef RAMMERAI_H_
#define RAMMERAI_H_

#include "AI.h"
#include "SFML\Graphics.hpp"

class Enemy; // forward declaration
class Entity;

class RammerAI : public AI
{
public:
	RammerAI(void);
	void computeMove(Enemy &enemy);
	void setSpeed(float);
	float getSpeed();
	void setMoveDistance(float);
	float getMoveDistance();
	void reset();
	~RammerAI(void);

private:
	sf::Vector2f currentEnemyToTarget;
	float speed;
	float moveDistance;
	int rotatingAngle;
	bool moving;
	sf::Vector2f moveFinishPos; // the position the enemy should be, after it finishes one movement
	int waiting;
	int distanceToTravel;
	int travelledDistance;
};

#endif