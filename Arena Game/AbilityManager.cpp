#include "AbilityManager.h"

AbilityManager::AbilityManager()
{
}

AbilityManager::~AbilityManager()
{
	
}

void AbilityManager::addAbility(Ability *ability)
{
	if(ability != NULL)
	{
		abilities.push_back(AbilityClock(ability));
	}
}

void AbilityManager::useAbility(const unsigned int index, const sf::Vector2f &position, const sf::Vector2f &direction, Entity *ownerPtr)
{ 
	PausableClock *pClockPtr = &abilities.at(index).pClock;
	Ability *ability = abilities.at(index).ability;
	if(index < abilities.size() && pClockPtr->getElapsedTime() >= ability->getRateOfFireLama())
	{
		ability->applyAbility(position, direction, ownerPtr);
		pClockPtr->restart();
	}
}

void AbilityManager::Flush()
{
	for(it = abilities.begin(); it != abilities.end(); it++)
	{
		delete it->ability;
	}
	abilities.clear();
}