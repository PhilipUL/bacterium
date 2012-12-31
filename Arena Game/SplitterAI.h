#ifndef SPLITTER_H_
#define SPLITTER_H_

#include "AI.h"
#include "Enemy.h"

class SplitterAI :public AI
{
public:
	SplitterAI(void);
	~SplitterAI(void);

	virtual void computeMove(Enemy& enemy);

private:
	sf::Vector2f direction    ;
	sf::Vector2f speed        ;
	Entity       targetPtr    ;
	Entity        enemy       ;
	float        currentAngle ;

};

#endif

