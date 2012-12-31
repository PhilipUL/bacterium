#ifndef SPREADSHOT_H_
#define SPREADSHOT_H_

#include "Ability.h"
#include "Projectile.h"
#include "InputHandler.h"

class SpreadShot : public Ability
{
public:
	SpreadShot(sf::Time rateOfFireLama);
	~SpreadShot();

	virtual void applyAbility(const sf::Vector2f &position, const sf::Vector2f &direction);
};
#endif