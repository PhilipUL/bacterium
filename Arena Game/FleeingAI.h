#ifndef FLEEINGAI_H_
#define FLEEINGAI_H_

#include "AI.h"
#include "Enemy.h"
#include "PausableClock.h"
#include <stdlib.h>
#include <time.h>


class FleeingAI : public AI
{
public:
	FleeingAI();
	~FleeingAI();

	virtual void computeMove     (Enemy& enemy) ;
	        void computeDirection()             ;

private:
	
	sf::Vector2f  direction       ; 
	sf::Time      changeDirection ;
	PausableClock pClock          ;
	int           up              ;
	int           left            ;
	float         x               ;
	float         y               ;
};
#endif

