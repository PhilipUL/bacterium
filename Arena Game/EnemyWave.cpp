#include "EnemyWave.h"


EnemyWave::EnemyWave()
	: active(false), index(0)
{
	
}

EnemyWave::EnemyWave(const EnemyWave &enemyWave)
{
	this->id = enemyWave.id;
	this->tier = enemyWave.tier;
	this->spawnTimeDelay = sf::Time(enemyWave.spawnTimeDelay);
	this->waveTimeDelay = sf::Time(enemyWave.waveTimeDelay);
	this->enemySpawns = enemyWave.enemySpawns;
	this->pClock = PausableClock(true);
	this->active = false;
	this->index = 0;
}


EnemyWave::~EnemyWave(void)
{

}

void EnemyWave::addEnemy(const std::string &name, const sf::Vector2f &spawnPosition)
{
	enemySpawns.push_back(EnemySpawn(name, spawnPosition));
}

void EnemyWave::Update(const std::vector<Entity*> &targets)
{
	//if we have spawned all enemies, this wave is done
	if(spawnedAllEnemies())
	{
		active = false;
	}
	//if we haven't reached the end of the wave and it's time to spawn the next enemy
	else if(targets.size() > 0 && index < enemySpawns.size() && pClock.getElapsedTime() >= spawnTimeDelay)
	{
		//pick random target for enemy
		Entity *targetPtr = (targets.at(rand() % targets.size()));	
		EntityBuilder::getInstance()->buildEnemy(enemySpawns[index].name, *targetPtr, enemySpawns[index].spawnPosition);
		index++;
		pClock.restart();
	}
}

void EnemyWave::restart()
{
	index = 0;
	pClock.resume();
	pClock.restart();
}
