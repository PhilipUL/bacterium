#ifndef ENEMYWAVE_H_
#define ENEMYWAVE_H_

#include "PausableClock.h"
#include "EntityBuilder.h"

class EnemyWave
{
public:
	EnemyWave();
	~EnemyWave();

	EnemyWave(const EnemyWave &EnemyWave);

	static const enum Tier {
		VERY_EASY = 1,
		EASY = 2,
		MEDIUM = 3,
		HARD = 4,
		VERY_HARD = 5
	};

	void setSpawnTimeDelay(sf::Time &spawnTimeDelay) { this->spawnTimeDelay = spawnTimeDelay; }
	void setWaveTimeDelay(sf::Time &waveTimeDelay) { this->waveTimeDelay = waveTimeDelay; }
	void setID(const std::string id) { this->id = id; }
	void setTier(const Tier tier) { this->tier = tier; }

	const sf::Time &getWaveTimeDelay() const { return waveTimeDelay; }
	const std::string getID() const { return id; }
	const Tier getTier() const { return tier; }

	const bool isActive() const { return active; }
	void activate() { active = true; restart(); }
	void deactivate() { active = false; }
	
	void addEnemy(const std::string &name, const sf::Vector2f &spawnPosition);
	
	bool spawnedAllEnemies() { return index == enemySpawns.size(); }

	void Update(const std::vector<Entity*> &targets);

	void pause() { pClock.pause(); }
	void resume() { pClock.resume(); }
	void restart();

private:
	struct EnemySpawn
	{
		EnemySpawn(const std::string &name, const sf::Vector2f &spawnPosition)
			:	name(name), spawnPosition(spawnPosition)
		{
		}

		EnemySpawn(EnemySpawn &enemySpawn)
		{
			this->name = enemySpawn.name;
			this->spawnPosition = sf::Vector2f(enemySpawn.spawnPosition);
		}

		std::string name;
		sf::Vector2f spawnPosition;
	};

	bool active;
	std::vector<EnemySpawn> enemySpawns;
	unsigned int index;
	PausableClock pClock;
	sf::Time spawnTimeDelay;

	//This is used to delay the wave until the wave clock has reached this time
	//and then we reset the wave clock for the next wave.
	sf::Time waveTimeDelay;

	//v10 code
	Tier tier;
	std::string id;
};

#endif

