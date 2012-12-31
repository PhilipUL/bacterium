#include "CollisionManager.h"
#include "Enemy.h"

void CollisionManager::collision(const vector<Entity*>& listA ,const vector<Entity*>& listB ,int reaction)
{
	force = sf::Vector2f(2.f,2.f) ;
	for(i = 0;i < listA.size() ;i++)
	{
		rectA  = listA[i] -> getRect();
		posA   = listA[i] -> getPos();
		speedA = listA[i] -> getSpeed();

		for(j = 0  ;j < listB.size() ;j++)
		{			
			if(listA[i] == listB[j])
			{
				continue;
			}

			rectB  = listB[j] -> getRect();
			posB   = listB[j] -> getPos();
			speedB = listB[j] -> getSpeed();

			if(rectA.intersects(rectB))
			{
				switch(reaction)
				{
					case 1:
					listB[j]->setActive(false);                                                   //Set the entity to inactive                //
					break;

					case 2:
						if(listA[i]->getType() == ENEMY || listA[i]->getType() == PLAYER)
						{
							Character *characterPtr = dynamic_cast<Character*>(listA[i]);
							characterPtr->onHit(listB[j]);

							if(listB[j]->getType() == DAMAGING_ENTITY)
							{
								//we don't want to apply any forces to listA[i] if they own listB[j]
								//so we skip the rest of the reaction implementation
								DamagingEntity *damagingEntityPtr = dynamic_cast<DamagingEntity*>(listB[j]);
								if(damagingEntityPtr->getOwnerPtr() == listA[i])
								{
									continue;
								}
							}
						}

						direction =  VectorFuncs::normalise(VectorFuncs::getDirection(posA,posB));  //Get the direction and normalise the vector//
						multA     =  VectorFuncs::mult(direction,speedA);                          //multiply it by the objects' speed         //

						//////OPEN DAY TEMP CODE ///////////
						if (listA[i]->getType() == PLAYER)
						{
							dynamic_cast<Player*>(listA[i])->move(-multA);
						}
						else
						////////END OPEN DAY///////////////
						listA[i]  -> setPos(posA - multA);                                        //Apply a force to the object to push it in //
						                                                                          //the opposite direction                    //
					break;

					case 3:
						if(listB[j]->getType() == ENEMY && listA[i]->getType() == PLAYER) // only rammers should be able to push players
						{
							Enemy *enemy = dynamic_cast<Enemy*>(listB[j]);
							if(enemy->getBehaviour()->getType() == AI::RAMMER)
							{
								direction =  VectorFuncs::normalise(VectorFuncs::getDirection(posA, posB)); //Same as above but does not make an entity //
								multA     =  VectorFuncs::mult(direction, speedA);                         //inactive                                  //
								listA[i]  -> setPos(posA - multA + force);    
							}
						} 
						else if(listB[j]->getType() == PLAYER) // player should be able to push around all enemies, except Rammers
						{
							if(listA[i]->getType() == ENEMY)
							{
								Enemy *enemy = dynamic_cast<Enemy*>(listA[i]);
								if(enemy->getBehaviour()->getType() != AI::RAMMER)
								{
									direction =  VectorFuncs::normalise(VectorFuncs::getDirection(posA, posB)); //Same as above but does not make an entity //
									multA     =  VectorFuncs::mult(direction, speedA);                         //inactive                                  //
									listA[i]  -> setPos(posA - multA + force);    
								}
							}
						} else {
								direction =  VectorFuncs::normalise(VectorFuncs::getDirection(posA, posB)); //Same as above but does not make an entity //
								multA     =  VectorFuncs::mult(direction, speedA);                         //inactive                                  //
								listA[i]  -> setPos(posA - multA + force);    
						}
						                                                                                          
					break;

					case 4:

						direction =  VectorFuncs::normalise(VectorFuncs::getDirection(posA,posB)); //Same as above only with two objects       //
						multA     =  VectorFuncs::mult(direction,speedA + force);
						multB     =  VectorFuncs::mult(direction,speedB);
						listA[i]  -> setPos(posA - multA);
						listB[j]->setPos(posB + multB);
					break;


				}
			}
		}
	}
}

void CollisionManager::checkBounds(const vector<Entity*>& entities, const sf::RenderWindow& window)
{
	const sf::Vector2f *pos;
	const sf::Vector2f *speed;
	const sf::Vector2u *textureSize;
	const sf::Vector2u *winSize;

	for(unsigned int i = 0 ; i < entities.size() ; i++)
	{
		pos         = &entities[i] -> getPos();
		speed       = &entities[i] -> getSpeed();
		textureSize = &entities[i] -> getSprite().getTexture() -> getSize();
		winSize     = &window.getSize();

		if (pos->x < 0)
		{
			entities[i]->setPos(sf::Vector2f(0, pos->y));
		}
		else if (pos->y < 0)
		{
			entities[i]->setPos(sf::Vector2f(pos->x,0));
		}
		else if (pos->x + textureSize->x / 4 >= winSize->x)
		{
			entities[i]->setPos(sf::Vector2f((float)winSize->x - textureSize->x/4,pos->y));
		}
		else if (pos->y + textureSize->y / 4 >=  winSize->y)
		{
			entities[i]->setPos(sf::Vector2f(pos->x,(float)winSize->y - textureSize->y/4));
		}
	}

}
