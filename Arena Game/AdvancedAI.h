#ifndef ADVANCEDAI_H_
#define ADVANCEDAI_H_

#include "AI.h"
#include "SFML\Graphics.hpp"


class Enemy; // forward declaration
class DamagingEntity;
class Entity;

class AdvancedAI : public AI
{
public:
	AdvancedAI(); // Constructor
	~AdvancedAI();

	void computeMove(Enemy &enemy); // the forward declaration makes sure that Enemy has been declared 
	void setDodgeDamagingEntity(DamagingEntity &damagingEntity);
	const DamagingEntity* getDodgeDamagingEntity() const;

	bool needToDodge(DamagingEntity *, Enemy &enemy, int angle); // checks to see if the bullet is moving withen 10 degrees in our direction
	
	void setSpeed(float);
	float getSpeed();

	void setDodgeSpeed(float);
	float getDodgeSpeed();

private:
	bool dodgeState;
	sf::Vector2f dodgeVector;

	bool dodgingDamagingEntity;
	bool dodgeDestination;
	bool reachDestination;
	DamagingEntity* dodgeDamagingEntity; // The damaging entity that the dodge state will try to dodge
	sf::Vector2f dodgeFinishPos; // The destination of the dodge that will be calculated by the dodge state
	sf::Vector2f currentEnemyToTarget;
	int rotatingAngle;

	float speed;
	float dodgeSpeed;
};

#endif