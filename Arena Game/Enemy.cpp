#include "Enemy.h"

#include "ParticleEmitterBuilder.h"

Enemy::Enemy()
{
	type  = ENEMY;
	targetPtr = NULL;
	behaviourPtr = NULL;
}

Enemy::~Enemy()
{
	delete behaviourPtr;
}

void Enemy::Flush()
{
	Character::Flush();
}

void Enemy::setBehaviour(AI *behaviourPtr)
{
	if(behaviourPtr != NULL)
	{
		this->behaviourPtr = behaviourPtr;
	}
}

void Enemy::setTarget(const Entity *targetPtr)
{
	if(targetPtr != NULL)
		this->targetPtr = targetPtr;
}

void Enemy::Update()
{
	// the current behaviourPtr computes the move to make,
	if(behaviourPtr != NULL)	
		behaviourPtr->computeMove(*this);

	Character::Update();
}

void Enemy::move(const sf::Vector2f &movement)
{
	setPos(getPos() + movement);
}

void Enemy::setDamagingList(const std::vector<Entity *> *listPtr)
{
	this->damagingList = listPtr;
}

const std::vector<Entity *> *Enemy::getDamagingList() const
{
	return damagingList;
}

void Enemy::onHit(Entity *entityPtr)
{
	if(entityPtr != NULL)
	{
		if(entityPtr->getType() == DAMAGING_ENTITY)
		{
			DamagingEntity *damagingEntityPtr = dynamic_cast<DamagingEntity*>(entityPtr);
			setHealth(health - damagingEntityPtr->getDamage());
			if(damagingEntityPtr->getSubType() != DamagingEntity::MELEE)
			{
				damagingEntityPtr->setActive(false);
			}
			if(health < 0 && damagingEntityPtr->getOwnerPtr()->getType() == PLAYER)
			{
				Player *playerPtr = dynamic_cast<Player*>(damagingEntityPtr->getOwnerPtr());
				playerPtr->addToScore(deathScore);
			}
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
