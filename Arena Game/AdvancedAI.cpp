#include "AdvancedAI.h"

#include "Enemy.h"
#include <time.h>
#include "EntityManager.h"
#include <vector>
#include "DamagingEntity.h"
#include <math.h>
#include "VectorFuncs.h"

#include <cmath>

#include "EntityManager.h"


AdvancedAI::AdvancedAI()
{
	//VectorOfAllDamagingEntitysPtr = EntityManager::getVector(PROJECTILE);
	dodgingDamagingEntity = false;
	dodgeDestination = false;
	reachDestination = false;
	
	dodgeState = false; // we start of in the ready state

	setSpeed(15);
	setDodgeSpeed(40);

	type = ADVANCED;
}

void AdvancedAI::computeMove(Enemy &enemy)
{
	//vector<Entity*> &VectorOfAllDamagingEntitysPtr = EntityManager::getVector(PROJECTILE);
	vector<Entity*> VectorOfAllDamagingEntitysPtr = *enemy.getDamagingList();
	//cout << "number of projectiles = " << VectorOfAllDamagingEntitysPtr.size() << endl;

	if(!dodgingDamagingEntity) // if we're not currently dodging a projectile
	{

		for(unsigned int j = 0; j < VectorOfAllDamagingEntitysPtr.size(); j++) // check if bullets are in range and traveling in a direction 10 degrees 
		{
			// only try and dodge bullets when they are a certain distance away (close bullets)
			// distance formula sqrt(pow(x2-x1),2)+pow(y2-y1),2))
		
			int distance = (int)sqrt( pow((VectorOfAllDamagingEntitysPtr[j]->getPos().x - enemy.getPos().x) ,2) + pow((VectorOfAllDamagingEntitysPtr[j]->getPos().y - enemy.getPos().y), 2) );

		//cout << "distance[" << j << "] = " << distance << endl; // 150 sounds like a looks like a good distance to dodge from

			if (distance <= 70)
			{
				DamagingEntity *ptrBullet = dynamic_cast<DamagingEntity*>(VectorOfAllDamagingEntitysPtr[j]);

				if(ptrBullet->getSubType() == DamagingEntity::PROJECTILE && needToDodge(ptrBullet, enemy, 30))
				{
					//cout << " bullets need to be dodged " << endl;
					//cout << " bullet vector size = " << bulletsToDodge.size() << endl;
					//setDodgeDamagingEntity(*dynamic_cast<DamagingEntity*>(bulletsToDodge[0]));
					
					setDodgeDamagingEntity(*dynamic_cast<DamagingEntity*>(VectorOfAllDamagingEntitysPtr[j]));
					dodgingDamagingEntity = true; // now we're doding a projectile

					//bulletsToDodge.push_back(VectorOfAllDamagingEntitysPtr[j]);
				}
			} else if (distance <= 150)
			{
				// see if any of these need to be dodged
				DamagingEntity *ptrBullet = dynamic_cast<DamagingEntity*>(VectorOfAllDamagingEntitysPtr[j]);

				if(ptrBullet->getSubType() == DamagingEntity::PROJECTILE && needToDodge(ptrBullet, enemy, 10))
				{
					//cout << " bullets need to be dodged " << endl;
					//cout << " bullet vector size = " << bulletsToDodge.size() << endl;
					//bulletsToDodge.push_back(VectorOfAllDamagingEntitysPtr[j]);

					setDodgeDamagingEntity(*dynamic_cast<DamagingEntity*>(VectorOfAllDamagingEntitysPtr[j]));
					dodgingDamagingEntity = true; // now we're doding a projectile

				}
			}
		}
		if(dodgingDamagingEntity != true)// if we don't need to dodge anything then just move as normal
		{
			currentEnemyToTarget = enemy.getTarget()->getPos() - enemy.getPos(); // create the direction vector
			currentEnemyToTarget = VectorFuncs::normalise(currentEnemyToTarget);

			currentEnemyToTarget.x = currentEnemyToTarget.x *getSpeed();
			currentEnemyToTarget.y = currentEnemyToTarget.y *getSpeed();
			enemy.move(currentEnemyToTarget);

			//currentEnemyToTarget = VectorFuncs::getDirection(enemy.getPos(), enemy.getTarget()->getPos());
			rotatingAngle = (int)VectorFuncs::getAngle(currentEnemyToTarget);
			enemy.setRotation((float)-rotatingAngle);
			//enemy.move(currentEnemyToTarget);
			
		}

	

	}else{ // if we're in the dodge state

		//if(dodgeFinishPos.x == NULL) // if a dodge destination hasn't been set
		if(!dodgeDestination) // if we don't have a dodge destination
		{
			//cout << " calculating dodge destination " << endl;
			sf::Vector2f bulletVelocity = *getDodgeDamagingEntity()->getVelocity();
			bulletVelocity = VectorFuncs::normalise(bulletVelocity);

			sf::Vector2f playerToEnemy = enemy.getPos() - enemy.getTarget()->getPos();
			playerToEnemy = VectorFuncs::normalise(playerToEnemy);

			int bulletAngle = (int)VectorFuncs::getAngle(bulletVelocity);
			int enemyAngle = (int)VectorFuncs::getAngle(playerToEnemy);
			int deltaAngle = enemyAngle - bulletAngle; // if negitive, go dodge in one direction, else dodge in the other

			if(deltaAngle < 0)
			{
				dodgeVector = VectorFuncs::rotate(bulletVelocity, 90.0); // creates a vector that is 90 degrees to the direction of the oncoming bullet
			} else {
				dodgeVector = VectorFuncs::rotate(bulletVelocity, -90.0); // creates a vector that is 90 degrees to the direction of the oncoming bullet
			}
			dodgeVector = VectorFuncs::normalise(dodgeVector);  // normalises that vector

			//ai->enemy.move(dodgeVector); // moves using that vector

			if(dodgeVector.x == 0 && dodgeVector.y == 0) // if the dodgeVector is zero, we need to make one up
			{
				//cout << "oh sheet" << endl;
				float xDistance = std::abs(enemy.getPos().x - enemy.getTarget()->getPos().x);
				float yDistance = std::abs(enemy.getPos().y - enemy.getTarget()->getPos().y);

				if(enemy.getPos().x < enemy.getTarget()->getPos().x) // enemy is to the left
				{
					// so dodge up or down
					dodgeVector.y = .5;
				}
				//else right of target
				else
				{
					dodgeVector.y = -.5;
				}

				//if above target
				if(enemy.getPos().y < enemy.getTarget()->getPos().y)
				{
					dodgeVector.x = .5;
				}
				//else below target
				else
				{
					dodgeVector.x = -.5;
				}
				
			}

			this->dodgeFinishPos.x = (dodgeVector.x)*80 + (enemy.getPos().x);
			this->dodgeFinishPos.y = (dodgeVector.y)*80 + (enemy.getPos().y);

			dodgeVector.x = dodgeVector.x * getDodgeSpeed();  // dodgeVector dectates the speed at which the enemy will dodge
			dodgeVector.y = dodgeVector.y * getDodgeSpeed();  //

			dodgeDestination = true; // now we have a dodge destination.

			//cout << "Dodge Vector x = " << dodgeVector.x << " , y = " << dodgeVector.y << endl;

		}else{ // if it has
			
			if(dodgeVector.x > 0) // if the dodge vector of x is greater then zero, then we will be at the destination, if the current enemy x is greater then the dodge destination
			{

				if(enemy.getPos().x > this->dodgeFinishPos.x) // check if we've reached destination
				{
					reachDestination = true;
					// we have, so set the reachDestination boolean to true

					//cout << " at destintation " << endl;
					// if it has been reached
					// then set projectiles to dodge back to null
					this->dodgeFinishPos.x = 0;
					this->dodgeFinishPos.y = 0;
					dodgeDamagingEntity = NULL;

					//this->bulletsToDodge.clear();
					//cout << "clearing bulletsToDodge vector" << endl;

					dodgingDamagingEntity = false;
					dodgeDestination = false;

				} else {
					// if we haven't reached the destination then keep moving
					
					enemy.move(dodgeVector);
				}

			}else{ // we will be at the destination if the enemy x is less then the dodge destination

				if(enemy.getPos().x < this->dodgeFinishPos.x) // check if we've reached destination
				{
					reachDestination = true;
					// we have, so set the reachDestination boolean to true

					//cout << " at destintation " << endl;
					// if it has been reached
					// then set projectiles to dodge back to null
					this->dodgeFinishPos.x = 0;
					this->dodgeFinishPos.y = 0;
					dodgeDamagingEntity = NULL;

					//this->bulletsToDodge.clear();
					//cout << "clearing bulletsToDodge vector" << endl;

					dodgingDamagingEntity = false;
					dodgeDestination = false;

				} else {
					// if we haven't reached the destination then keep moving
					enemy.move(dodgeVector);
				}

			}

				
			

		}
	}


}

bool AdvancedAI::needToDodge(DamagingEntity *ptr, Enemy &enemy, int angle) // checks to see if the bullet is moving withen 10 degrees in our direction
{

	float unitLengthV1;
	float unitLengthV2;
	float topLine;
	float bottomLine;
	float cal;
	float resultInRad;
	float resultInDeg;

	sf::Vector2f dodgeVector;

	sf::Vector2f BulletVelocity= *ptr->getVelocity();
	
	sf::Vector2f bulletToEnemy = enemy.getPos() - ptr->getPos();
	sf::Vector2f bulletVelocity = *ptr->getVelocity();
	
	unitLengthV1 = sqrt((bulletToEnemy.x*bulletToEnemy.x) + (bulletToEnemy.y*bulletToEnemy.y));
	unitLengthV2 = sqrt((bulletVelocity.x*bulletVelocity.x) + (bulletVelocity.y*bulletVelocity.y));

	topLine = ((bulletToEnemy.x*bulletVelocity.x)+(bulletToEnemy.y*bulletVelocity.y));
	bottomLine = (unitLengthV1*unitLengthV2);

	cal = topLine/bottomLine;

	resultInRad  = acos(cal);
	resultInDeg = float(resultInRad * 180.0f / PI);

	//cout << "angle equals: " << resultInDeg << endl;

	if(resultInDeg <= angle)
	{
		return true;
	}else{
	
		return false;
	}
}

void AdvancedAI::setDodgeDamagingEntity(DamagingEntity &proj)
{
	this->dodgeDamagingEntity = &proj;
}

const DamagingEntity* AdvancedAI::getDodgeDamagingEntity() const
{
	return this->dodgeDamagingEntity;
}

void AdvancedAI::setSpeed(float s)
{
	this->speed = (s/10);
}

float AdvancedAI::getSpeed()
{
	return speed;
}

void AdvancedAI::setDodgeSpeed(float s)
{
	this->dodgeSpeed = (s/10);
}

float AdvancedAI::getDodgeSpeed()
{
	return dodgeSpeed;
}