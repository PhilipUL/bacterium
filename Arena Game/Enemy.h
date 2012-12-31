#ifndef ENEMY_H_
#define ENEMY_H_

#include "Character.h"

#include "SimpleAI.h"
#include "AdvancedAI.h"
#include "RammerAI.h"
#include "FleeingAI.h"
#include "SplitterAI.h"
#include "SplitletsAI.h"
#include "GravityAI.h"
#include "DefensiveAI.h"

#include "Player.h"

class Enemy : public Character
{
public:
	Enemy();
	~Enemy();

	virtual void Flush();

	virtual void Update();
	virtual void move(const sf::Vector2f &movement);
	virtual void onHit(Entity *entityPtr);
	
	void setBehaviour(AI *behaviourPtr);
	void setTarget(const Entity *targetPtr);

	const Entity *getTarget() const { return targetPtr; }
	const AI *getBehaviour() const { return behaviourPtr; }

	void setDamagingList(const std::vector<Entity *> *listPtr);
	const std::vector<Entity *> *getDamagingList() const;

private:
	const Entity *targetPtr;
	AI *behaviourPtr;

	const std::vector<Entity *> *damagingList;
};

#endif
