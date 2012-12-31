#ifndef AI_H_
#define AI_H_

class Enemy;

class AI
{
public:
	virtual void computeMove(Enemy &enemy) = 0;

static const enum AITYPE
	{ABSORBING,
     ADVANCED,
     BASIC,
     DEFENSIVE,
     FLEEING,
	 GRAVITY,
     SIMPLE,
	 SPLIT,
	 SPLITLETS,
	 RAMMER};

	AITYPE getType() const {return type;}

	
protected:
	AITYPE type;
};

#endif
