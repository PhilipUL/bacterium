#ifndef CHARACTER_H_
#define CHARACTER_H_

#include "AnimatedEntity.h"
#include "AbilityManager.h"
#include "DamagingEntity.h"

class Character : public AnimatedEntity
{
public:
	Character();
	~Character();

	virtual void Flush();

	void useAbility(const int abilityIndex, sf::Vector2f &direction);

	void addAbility(Ability *ability);

	virtual void onHit(Entity *entityPtr) = 0;

	void setHealth(const float health) { this->health = health; }
	void setMaxHealth(const float maxHealth) { this->maxHealth = maxHealth; }

	const float getHealth() const { return health; }
	const float getMaxHealth() const { return maxHealth; }

	void setHitDamage(const float hitDamage) { this->hitDamage = hitDamage; }
	const float getHitDamage() const { return hitDamage; }

	void setDeathScore(const int score) { this->deathScore = score; }
	const int getDeathScore() const { return deathScore; }

protected:
	AbilityManager abilityManager;

	float health;
	float maxHealth;
	float hitDamage;
	int deathScore;
};
#endif
