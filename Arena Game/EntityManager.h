#ifndef ENTITYMANAGER_H_
#define ENTITYMANAGER_H_

#include "Global.h"
#include "EntityTypes.h"
#include "CollisionManager.h"
#include "IUpdatable.h"

class EntityManager
{
public:
	EntityManager();
	~EntityManager();

	/*
	*Entity updates if in this list 
	*/
	void addUpdatable(IUpdatable *updatableEntityPtr, TYPE type);

	/*
	*Adds an entity to entity list
	*/
	void addEntity(Entity *entityPtr);

	/*
	*Removes all the entities from the list
	*/
	void Flush();

	/*
	*Checks if the entity given is on screen 
	*/
	bool isOnScreen(const Entity &entity, const sf::IntRect &viewport) const ;

	/*
	*Drawing all entities in the drawable list
	*who are on the screen
	*/
	void Draw(sf::RenderWindow& window);

	/*
	*Updates all entities in the updatable list
	*/
	void Update(const sf::RenderWindow& window);

	/*
	*Container method for checking collision
	*/
	void checkCollision(const sf::RenderWindow& window);

	/*
	*Returns a vector given a type
	*/
	const vector<Entity*> *getVector(TYPE type) const;

private:
	vector<Entity*> danYoureOffTheTeam[NUM_TYPES];
	vector<IUpdatable*> danIsSilly[NUM_TYPES];

	unsigned int i, j;

	CollisionManager collision;

	/*
	*erases a single entity from the updatable list
	*/
	void eraseInUpdatable(Entity *entityPtr);
};
#endif
