#include "DamagingEntity.h"


DamagingEntity::DamagingEntity(void)
{
	type = DAMAGING_ENTITY;
}


DamagingEntity::~DamagingEntity(void)
{
}

void DamagingEntity::Update()
{	
	if(lifeTime > sf::milliseconds(0) && pClock.getElapsedTime() >= lifeTime)
	{
		active = false;
		pClock.restart();
	}

	if(subType == MELEE)
	{
		if(ownerPtr != NULL)
		{
			setPos(ownerPtr->getPos());
		}
	}
	else
	{
		setPos(getPos() + velocity);
		//if a non-melee damaging entity is keeping track of it's owner
		//do we want to do something here?
	}

	AnimatedEntity::Update();
}

void DamagingEntity::pause()
{
	pClock.pause();
}

void DamagingEntity::resume()
{
	pClock.resume();
}

void DamagingEntity::setVelocity(const sf::Vector2f &direction, const sf::Vector2f &speed)
{
	velocity = VectorFuncs::mult(VectorFuncs::normalise(direction), speed);
}
