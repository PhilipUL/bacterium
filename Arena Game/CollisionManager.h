#ifndef COLLISIONMANAGER_H_
#define COLLISIONMANAGER_H_

#include "Global.h"
#include "Player.h" 

class CollisionManager
{
public:
	/*
	*Collision takes in two lists and an int as 
	*parameters, it checks to see if any entities 
	*in both lists are colliding and depending on 
	*the int passed in will produce a reaction.The 
	*algorithm uses a "Brute force" approach to 
	*finding pairs.
	*/

	///reactions//////////////////////////////////////
	//1 = ENTITY IN LISTB BECOMES INACTIVE
	//2 = STOP ENTITY IN LISTA AND KILL ENTITY IN LISTB
	//3 = STOP ENTITY IN LISTA
	//4 = STOP BOTH ENTITIES
	//..
	//..
	//////////////////////////////////////////////////
	void collision(const vector<Entity*>& listA, const vector<Entity*>& listB, int reaction);

	/*
	*Checks the bounds for the entity that is passed in, 
	*the implemetation wil be modified later to allow 
	*scrolling instead of staying still at the border 
	*
	*WARNING: MAY NOT BE NEEDED
	*/
	void checkBounds(const vector<Entity*>& entites, const sf::RenderWindow& window);

private:
	unsigned int i		   ;
	unsigned int j		   ;

	sf::IntRect rectA      ;
	sf::IntRect rectB	   ;
	sf::Vector2f posA	   ;
	sf::Vector2f posB	   ;
	sf::Vector2f speedA	   ;
	sf::Vector2f speedB	   ;
	sf::Vector2f direction ;
	sf::Vector2f multA	   ;
	sf::Vector2f multB	   ;
    sf::Vector2f force     ;
};

#endif

//#ifndef COLLISIONMANAGER_H_
//#define COLLISIONMANAGER_H_
//
//#include "Global.h"
//#include "Entity.h"
//
//class CollisionManager
//{
//public:
//	/*
//	*Collision takes in two lists and an int as 
//	*parameters, it checks to see if any entities 
//	*in both lists are colliding and depending on 
//	*the int passed in will produce a reaction.The 
//	*algorithm uses a "Brute force" approach to 
//	*finding pairs.
//	*/
//
//	///reactions//////////////////////////////////////
//	//1 = ENTITY IN LISTB BECOMES INACTIVE
//	//2 = STOP ENTITY IN LISTA AND KILL ENTITY IN LISTB
//	//3 = STOP ENTITY IN LISTA
//	//4 = STOP BOTH ENTITIES
//	//..
//	//..
//	//////////////////////////////////////////////////
//	void collision(const vector<Entity*>& listA, const vector<Entity*>& listB, int reaction);
//
//	/*
//	*Checks the bounds for the entity that is passed in, 
//	*the implemetation wil be modified later to allow 
//	*scrolling instead of staying still at the border 
//	*
//	*WARNING: MAY NOT BE NEEDED
//	*/
//	void checkBounds(const vector<Entity*>& entites, const sf::RenderWindow& window);
//};
//
//#endif
//
