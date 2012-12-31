#include "Player.h"


Player::Player()
{
	type = PLAYER;

	//TEMP
	setPrimaryAttack(0);
	setSpecialAttack(1);
	setMeleeAttack(2);
	setTrapAttack(3);

	setScore(0);
}

Player::~Player()
{
}

void Player::move(sf::Vector2f &movement)
{
	////////// OPEN DAY TEMP CODE ///////////////
	if(getPos().x + movement.x < getRect().width / 2 ||
		getPos().x + movement.x > 800 - getRect().width / 2)
	{
		movement.x = 0;
	}
	if(getPos().y + movement.y < getRect().height / 2 ||
		getPos().y + movement.y > 600 - getRect().height / 2)
	{
		movement.y = 0;
	}
	/////////////////END OPEN DAY//////////////////////
	
	setPos(getPos() + movement);
}

void Player::onHit(Entity *entityPtr)
{
	if(entityPtr != NULL)
	{
		if(entityPtr->getType() == DAMAGING_ENTITY)
		{
			DamagingEntity *damagingEntityPtr = dynamic_cast<DamagingEntity*>(entityPtr);
			if(damagingEntityPtr->getOwnerPtr() != this)
			{
				setHealth(health - damagingEntityPtr->getDamage());
				if(damagingEntityPtr->getSubType() != DamagingEntity::MELEE)
				{
					damagingEntityPtr->setActive(false);
				}
			}
		}
		else if(entityPtr->getType() == ENEMY)
		{
			setHealth(health - dynamic_cast<Character*>(entityPtr)->getHitDamage());
		}

		if(health < 0)
		{
			//emit death particle effect
			this->loadHitEmitter();
			//play sound
			this->playHitSound();
			//set to inactive 
			setActive(false);
		}
	}

}