#ifndef ENTITYBUILDER_H_
#define ENTITYBUILDER_H_

#include <string>
#include <SFML\Graphics.hpp>

#include "EntityTypes.h"
#include "EntityManager.h"
#include "Player.h"
#include "Enemy.h"
#include "TextureManager.h"
#include "EntityResourceManager.h"
#include "DamagingEntity.h"

class EntityBuilder
{
public:
	static EntityBuilder *getInstance();

	void init(EntityResourceManager *entityResourcePtr, EntityManager *entityManagerPtr);
	void release();

	Entity *buildEntity(const std::string filepath, const sf::Vector2f &position);
	Entity *buildPlayer(const std::string filepath, const sf::Vector2f &position);
	Entity *buildEnemy(const std::string filepath, const Entity &target, const sf::Vector2f &position);
	Entity *buildDamaging(const std::string filepath, const sf::Vector2f &position, const sf::Vector2f &direction, Entity *ownerPtr);

private:
	EntityBuilder();
	~EntityBuilder();

	static EntityBuilder singleton;

	EntityResourceManager *entityResourcePtr;
	EntityManager *entityManagerPtr;
};

#endif

