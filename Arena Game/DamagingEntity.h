#ifndef DAMAGINGENTITY_H_
#define DAMAGINGENTITY_H_

#include "AnimatedEntity.h"

//Abilities use these entities
class DamagingEntity : public AnimatedEntity
{
public:
	DamagingEntity(void);
	~DamagingEntity(void);

	static const enum SubType
	{
		PROJECTILE,
		TRAP,
		MELEE
	};

	virtual void Update();

	void pause();
	void resume();

	void setSubType(const SubType subType) { this->subType = subType; }
	const SubType getSubType() const { return subType; }

	void setDamage(const float damage) { this->damage = damage; }
	const float getDamage() const { return damage; }

	void setLifeTime(const sf::Time &lifeTime) { this->lifeTime = lifeTime; }
	const sf::Time *getLifeTime() const { return &lifeTime; }

	void setVelocity(const sf::Vector2f &direction, const sf::Vector2f &speed);
	const sf::Vector2f *getVelocity() const { return &velocity; }

	void setOwner(Entity *ownerPtr) { this->ownerPtr = ownerPtr; }
	Entity *getOwnerPtr() const { return ownerPtr; }


private:
	float damage;
	sf::Time lifeTime;
	PausableClock pClock;
	sf::Vector2f velocity;
	SubType subType;
	Entity *ownerPtr;
};

#endif