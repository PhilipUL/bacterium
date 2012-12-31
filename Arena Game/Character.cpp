#include "Character.h"


Character::Character()
{
}

Character::~Character(void)
{
}

void Character::Flush()
{
	abilityManager.Flush();
	AnimatedEntity::Flush();
}

void Character::useAbility(const int index, sf::Vector2f &direction)
{
	if(index >= 0)
	{
		abilityManager.useAbility(index, this->getPos(), direction, this);
	}
}

void Character::addAbility(Ability *ability)
{
	if(ability != NULL)
	{
		abilityManager.addAbility(ability);
	}
}