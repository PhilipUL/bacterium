#include "EntityBuilder.h"

EntityBuilder EntityBuilder::singleton = EntityBuilder();

EntityBuilder::EntityBuilder()
{

}

EntityBuilder::~EntityBuilder()
{

}

EntityBuilder *EntityBuilder::getInstance()
{
	return &singleton;
}

void EntityBuilder::init(EntityResourceManager *entityResourcePtr, EntityManager *entityManagerPtr)
{
	if(entityResourcePtr != NULL)
	{
		this->entityResourcePtr = entityResourcePtr;
	}
	if(entityManagerPtr != NULL)
	{
		this->entityManagerPtr = entityManagerPtr;
	}
}

void EntityBuilder::release()
{
	
}

Entity *EntityBuilder::buildEntity(const std::string filepath, const sf::Vector2f &position)
{
	//since the basic entity does not contain any dynamically allocated memory (pointers),
	//we can use the default copy constructor
	const Entity *templatePtr = entityResourcePtr->getResource(filepath);
	if(templatePtr == NULL)
	{
		return NULL;
	}

	Entity *entityPtr = new Entity(*templatePtr);
	entityPtr->setPos(position);

	//Now the entity has been built, set it to active and add it to the manager
	entityPtr->setActive(true);
	entityManagerPtr->addEntity(entityPtr);

	return entityPtr;
}

Entity *EntityBuilder::buildPlayer(const std::string filepath, const sf::Vector2f &position)
{
	const Player *templatePtr = dynamic_cast<const Player*>(entityResourcePtr->getResource(filepath));
	if(templatePtr == NULL)
	{
		std::cerr << "Unable to build player " << filepath << std::endl;
		return NULL;
	}

	Player *playerPtr = new Player(*templatePtr);
	playerPtr->setScore(0);
	playerPtr->setPos(position);

	playerPtr->setActive(true);
	entityManagerPtr->addEntity(playerPtr);

	return playerPtr;
}

Entity *EntityBuilder::buildEnemy(const std::string filepath, const Entity &target, const sf::Vector2f &position)
{

	const Enemy *templatePtr = dynamic_cast<const Enemy*>(entityResourcePtr->getResource(filepath));
	if(templatePtr == NULL)
	{
		return NULL;
	}

	Enemy *enemyPtr = new Enemy(*templatePtr);

	enemyPtr->setPos(position);
	enemyPtr->setTarget(&target);
	enemyPtr->setDamagingList(entityManagerPtr->getVector(DAMAGING_ENTITY));

	AI::AITYPE behaviourType = templatePtr->getBehaviour()->getType();
	if(behaviourType == AI::RAMMER)
	{
		enemyPtr->setBehaviour(new RammerAI());
	}
	else if(behaviourType == AI::SIMPLE)
	{
		enemyPtr->setBehaviour(new SimpleAI());
	}
	else if(behaviourType == AI::ADVANCED)
	{
		enemyPtr->setBehaviour(new AdvancedAI());
	}
	else if(behaviourType == AI::FLEEING)
	{
		enemyPtr->setBehaviour(new FleeingAI());
	}
	else if(behaviourType == AI::SPLIT)
	{
		enemyPtr->setBehaviour(new SplitterAI());
	}
	else if(behaviourType == AI::SPLITLETS)
	{
		enemyPtr->setBehaviour(new SplitletsAI());
	}
	else if(behaviourType == AI::GRAVITY)
	{
		enemyPtr->setBehaviour(new GravityAI());
	}
	else if(behaviourType == AI::DEFENSIVE)
	{
		enemyPtr->setBehaviour(new DefensiveAI());
	}


	enemyPtr->setActive(true);
	entityManagerPtr->addEntity(enemyPtr);

	return enemyPtr;
}

Entity *EntityBuilder::buildDamaging(const std::string filepath, const sf::Vector2f &position, const sf::Vector2f &direction, Entity *ownerPtr)
{
	const DamagingEntity *templatePtr = dynamic_cast<const DamagingEntity*>(entityResourcePtr->getResource(filepath));
	if(templatePtr == NULL)
	{
		return NULL;
	}

	DamagingEntity *damagingPtr = new DamagingEntity(*templatePtr);

	damagingPtr->setPos(position);
	damagingPtr->setVelocity(direction, damagingPtr->getSpeed());
	damagingPtr->setOwner(ownerPtr);

	damagingPtr->setActive(true);
	entityManagerPtr->addEntity(damagingPtr);

	return damagingPtr;
}
