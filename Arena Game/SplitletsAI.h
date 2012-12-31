#ifndef SPLITLETS_H_
#define SPLITLETS_H_

#include "AI.h"
#include "Enemy.h"

class SplitletsAI : public AI
{
public:
	SplitletsAI(void);
	~SplitletsAI(void);

	void computeMove(Enemy& enemy);

private:
	sf::Vector2f direction ;
	sf::Vector2f speed     ;
	float currentAngle     ;
};
#endif