#include "Ability.h"
#include "EntityBuilder.h"

Ability::Ability()
{
}


Ability::~Ability()
{
}

void Ability::applyAbility(const sf::Vector2f &position, const sf::Vector2f &direction, Entity *ownerPtr)
{
	for(unsigned int i = 0; i < numEntities; i++)
	{
		//how to apply damage and speed multipliers??????????????
		EntityBuilder::getInstance()->buildDamaging(entityFilepath, position + entitySpawnOffset, VectorFuncs::rotate(direction, angleBetweenEntities * i), ownerPtr);
		if(sound.getBuffer() != NULL)
		{
			sound.play();
		}
	}
}
