#ifndef EXPLODINGTRAP_H_
#define EXPLODINGTRAP_H_

#include "Ability.h"
#include "ExplosiveTrap.h"

class ExplodingTrap : public Ability
{
public:
	ExplodingTrap(sf::Time rateOfFireLama);
	~ExplodingTrap();

	virtual void applyAbility(const sf::Vector2f &position, const sf::Vector2f &direction);
};
#endif