#include "EntityManager.h"


EntityManager::EntityManager()
{

}

EntityManager::~EntityManager()
{
	Flush();
}

void EntityManager::addEntity(Entity *entityPtr)
{
	if(entityPtr != NULL)
	{
		danYoureOffTheTeam[entityPtr->getType()].push_back(entityPtr);

		//check to see if it's an updatable entity
		IUpdatable *ptr = dynamic_cast<IUpdatable*>(entityPtr);
		if(ptr != NULL)
			addUpdatable(ptr, entityPtr->getType());
	}
}

void EntityManager::addUpdatable(IUpdatable *updatableEntityPtr, TYPE type)
{
	if(updatableEntityPtr != NULL)
		danIsSilly[type].push_back(updatableEntityPtr);
}

void EntityManager::Flush()
{
	for(i = 0 ; i < NUM_TYPES ; i++)
	{
		for(j = 0; j < danYoureOffTheTeam[i].size(); j++)
		{
			delete danYoureOffTheTeam[i][j];
		}
		danYoureOffTheTeam[i].clear();
		danIsSilly[i].clear();
	}
}

bool EntityManager::isOnScreen(const Entity &entity, const sf::IntRect& viewport) const 
{
	return viewport.intersects(entity.getRect());
}

void EntityManager::Draw(sf::RenderWindow &window)
{
	for(i = 0 ; i < NUM_TYPES ; i++)
	{
		for(j = 0; j < danYoureOffTheTeam[i].size(); j++)
		{
			Entity *entityPtr = danYoureOffTheTeam[i][j];
			////////////////////// TEST //////////////////////////////////
			if(i == DAMAGING_ENTITY)
			{
				if(!isOnScreen(*entityPtr, window.getViewport(window.getView())))
				{
					entityPtr->setActive(false);
				}
			}
			//////////////////////////////////////////////////////////////

			/*before we draw this entity, first we need to see if 
			*it is active. If it is not active, delete it from the lists
			*/
			if(!entityPtr->isActive())
			{
				eraseInUpdatable(entityPtr);
				danYoureOffTheTeam[i].erase(danYoureOffTheTeam[i].begin() + j);
				delete entityPtr;
				j--;
			}
			else if(isOnScreen(*entityPtr, window.getViewport(window.getView())))
			{
				/*if we got in here, the entity is still active and it
				*is currently on the screen, so draw it
				*/
				entityPtr->Draw(window);
			}
			
		}
	}
}

void EntityManager::Update(const sf::RenderWindow &window)
{
	//update all entities
	for(i = 0 ; i < NUM_TYPES ; i++)
	{
		for(j = 0; j < danIsSilly[i].size(); j++)
		{
			danIsSilly[i][j]->Update();
		}
	}
	
	checkCollision(window);
}

void EntityManager::eraseInUpdatable(Entity *entityPtr)
{
	/*
	*try to cast it to type updatable. If the cast is unsuccessful, then
	*the entity is not in the updatable list
	*/
	IUpdatable *ptr = dynamic_cast<IUpdatable*>(entityPtr);
	if(ptr != NULL)
	{
		//find which vector we need to iterate through to find it
		TYPE type = entityPtr->getType();
		//find the entity by reference and remove it
		for(unsigned int j = 0; j < danIsSilly[type].size(); j++)
		{
			if(danIsSilly[type][j] == ptr)
			{
				danIsSilly[type].erase(danIsSilly[type].begin() + j);
				//we found it, so we can break out since there is no need to keep looking
				break;
			}
		}
	}
}

void EntityManager::checkCollision(const sf::RenderWindow& window)
{
	//important that PLAYER is list A and ENEMY is list B
	collision.collision(danYoureOffTheTeam[PLAYER],danYoureOffTheTeam[ENEMY],2);

	//important that character lists is list A, and damaging entity list is list B!!!
	collision.collision(danYoureOffTheTeam[PLAYER],danYoureOffTheTeam[DAMAGING_ENTITY],2);
	collision.collision(danYoureOffTheTeam[ENEMY],danYoureOffTheTeam[DAMAGING_ENTITY],2);

	collision.collision(danYoureOffTheTeam[PLAYER],danYoureOffTheTeam[WALL],4);
	collision.collision(danYoureOffTheTeam[ENEMY],danYoureOffTheTeam[WALL],4);
	collision.collision(danYoureOffTheTeam[WALL],danYoureOffTheTeam[DAMAGING_ENTITY],1);

	collision.collision(danYoureOffTheTeam[ENEMY], danYoureOffTheTeam[ENEMY], 4);
}

const vector<Entity*> *EntityManager::getVector(TYPE type) const
{
	if(type != NUM_TYPES)
	{
		return &danYoureOffTheTeam[type];
	}
	return NULL;
}