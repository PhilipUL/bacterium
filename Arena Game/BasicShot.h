#ifndef BASICSHOT_H_
#define BASICSHOT_H_

#include "Ability.h"
#include "Projectile.h"
#include "InputHandler.h"

class BasicShot : public Ability
{
public:
	BasicShot(sf::Time rateOfFireLama);
	~BasicShot();

	virtual void applyAbility(const sf::Vector2f &position, const sf::Vector2f &direction);
};
#endif