#ifndef ABILITY_H_
#define ABILITY_H_

#include "PausableClock.h"
#include "SFML\Graphics.hpp"
#include "SFML\Audio.hpp"

#include "Entity.h"

class EntityBuilder;

class Ability
{
public:
	Ability();
	~Ability();
	
	virtual void applyAbility(const sf::Vector2f &position, const sf::Vector2f &direction, Entity *ownerPtr);

	void setRateOfFire(const sf::Time &rateOfFireLama) { this->rateOfFireLama = rateOfFireLama; }
	void setEntityFilepath(const std::string &filepath) { this->entityFilepath = filepath; }
	void setNumEntities(const unsigned int numEntities) { this->numEntities = numEntities; }
	void setAngleBetweenEntities(const float angle) { this->angleBetweenEntities = angle; }
	void setSpawnOffset(const sf::Vector2f &offset) { this->entitySpawnOffset = offset; }
	void setDamageMultiplier(const float multiplier) { this->damageMultiplier = multiplier; }
	void setSound(const sf::Sound &sound) { this->sound = sound; }

	//do we even need gets....
	const sf::Time getRateOfFireLama() const { return rateOfFireLama; }
	const std::string getEntityFilepath() const { return entityFilepath; }
	const unsigned int getNumEntities() const { return numEntities; }
	const float getAngleBetweenEntities() const { return angleBetweenEntities; }
	const sf::Vector2f getEntitySpawnOffset() const { return entitySpawnOffset; }
	const float getDamageMultiplier() const { return damageMultiplier; }

private:
	sf::Time rateOfFireLama;
	std::string entityFilepath;
	unsigned int numEntities;
	float angleBetweenEntities;
	sf::Vector2f entitySpawnOffset;
	float damageMultiplier;

	sf::Sound sound;

};
#endif
