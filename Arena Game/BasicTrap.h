#ifndef BASICTRAP_H_
#define BASICTRAP_H_

#include "Ability.h"
#include "Trap.h"

class BasicTrap : public Ability
{
public:
	BasicTrap(sf::Time rateOfFireLama);
	~BasicTrap();

	virtual void applyAbility(const sf::Vector2f &position, const sf::Vector2f &direction);
};
#endif