#include "RammerAI.h"

#include "Enemy.h"

RammerAI::RammerAI(void)
{
	setSpeed(20);
	setMoveDistance(250);
	moving = false;
	waiting = 30;
	distanceToTravel = 0;
	travelledDistance = 0;
	type = RAMMER;
}

void RammerAI::computeMove(Enemy &enemy)
{
	//std::cout << currentEnemyToTarget.x << ", " << currentEnemyToTarget.y << std::endl;
	// movement

	if(moving == false && waiting >= 30)
	{
		//cout << "calculating++++++++++++++++++++++++++++++++" << endl;

		// calculate the movement vector
		currentEnemyToTarget = enemy.getTarget()->getPos() - enemy.getPos();
		currentEnemyToTarget = VectorFuncs::normalise(currentEnemyToTarget);

		currentEnemyToTarget.x = currentEnemyToTarget.x *getSpeed();
		currentEnemyToTarget.y = currentEnemyToTarget.y *getSpeed();

		// after calculating our movement vector, we set moving bool to true, so that we can now start moving
		moveFinishPos.x = (currentEnemyToTarget.x * getMoveDistance()) + enemy.getPos().x;
		moveFinishPos.y = (currentEnemyToTarget.y * getMoveDistance()) + enemy.getPos().y;

		currentEnemyToTarget.x = currentEnemyToTarget.x * getSpeed(); 
		currentEnemyToTarget.y = currentEnemyToTarget.y * getSpeed();


		//distance formula sqrt(pow(x2-x1),2)+pow(y2-y1),2))
		distanceToTravel = (int)sqrt(pow((moveFinishPos.x - enemy.getPos().x), 2) + pow((moveFinishPos.y - enemy.getPos().y), 2));

		/*cout << "enemy.getPos().x " << enemy.getPos().x << endl;
		cout << "enemy.getPos().y " << enemy.getPos().y << endl;
		
		
		cout << "currentEnemyToTarget.x " << currentEnemyToTarget.x << endl;
		cout << "currentEnemyToTarget.y " << currentEnemyToTarget.y << endl;


		cout << "moveFinishPos.x " << moveFinishPos.x << endl;
		cout << "moveFinishPos.y " << moveFinishPos.y << endl;*/

		moving = true;
		waiting = 0;

	} else if(moving == true)
	{ // we are moving

		
		// if we've reached our destination
		//cout << "distanceToTravel " << distanceToTravel<< endl;

		//cout << "travelledDistance " << travelledDistance << endl;
		
		if(travelledDistance >= distanceToTravel)
		{
			//cout << "at destination" << endl;
			moving = false;
			moveFinishPos.x = 0;
			moveFinishPos.y = 0;
			distanceToTravel = 0;
			travelledDistance = 0;
		}else{
			//cout << "moving" << endl;

			enemy.move(currentEnemyToTarget);
			
			travelledDistance =  travelledDistance + (int)getSpeed();
		}
	} else if(waiting < 30)
	{
		if(waiting == 1)
		{
			//cout << "waiting " << waiting << endl;
		}
		waiting++;
	}
	

			
	//currentEnemyToTarget = VectorFuncs::getDirection(enemy.getPos(), enemy.getTarget()->getPos());
	rotatingAngle = (int)VectorFuncs::getAngle(currentEnemyToTarget);
	enemy.setRotation((float)-rotatingAngle);
}

void RammerAI::setSpeed(float s)
{
	this->speed = (s/10);
}

float RammerAI::getSpeed()
{
	return speed;
}

void RammerAI::setMoveDistance(float d)
{
	this->moveDistance = (d/10);
}

float RammerAI::getMoveDistance()
{
	return moveDistance;
}

void RammerAI::reset()
{
	moving = false;
	moveFinishPos.x = 0;
	moveFinishPos.y = 0;
	waiting = 30;
}

RammerAI::~RammerAI(void)
{
}
