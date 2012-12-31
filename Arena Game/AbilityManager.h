#ifndef ABILITYMANAGER_H_
#define ABILITYMANAGER_H_

#include "Ability.h"

class AbilityManager
{
public:
	AbilityManager();
	~AbilityManager();

	//adds an ability
	void addAbility(Ability *ability);

	//Uses particular ability
	void useAbility(const unsigned int index, const sf::Vector2f &position, const sf::Vector2f &direction, Entity *ownerPtr);

	//Deletes all abilities from the manager and clears the map
	void Flush();

private:
	struct AbilityClock
	{
		AbilityClock(Ability *ability)
			: ability(ability)
		{
		}

		PausableClock pClock;
		Ability *ability;
	};

	std::vector<AbilityClock> abilities;
	std::vector<AbilityClock>::const_iterator it;
};

#endif //ABILITYMANAGER