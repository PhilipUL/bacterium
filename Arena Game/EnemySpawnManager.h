#ifndef ENEMYSPAWNMANAGER_H_
#define ENEMYSPAWNMANAGER_H_

#include "EnemyWave.h"
#include "EntityManager.h"

//for file reading
#include "json\json.h"
#include <fstream>
//end file reading

class EnemySpawnManager
{
public:
	EnemySpawnManager();
	~EnemySpawnManager();
	
	void load(const Json::Value &root, EntityManager *entityManagerPtr, int mode);

	//keeps the spawn manager updated
	void Update(const std::vector<Entity*> &targets);

	bool spawnedAllWaves() { return index == levelWaves.size(); }
	const bool hasPlayerWon() const { return playerWon; }

	void pause();
	void resume();
	void restart();

	void flush();

private:
	EntityManager *entityManagerPtr;
	int mode;
	//handles activating the next wave
	PausableClock waveClock;
	//handles either the end state in normal, or difficulty in survival
	PausableClock modeClock;
	sf::Time waveTimeDelay;

	//normal mode
	unsigned int index;
	bool playerWon;

	//survival mode
	EnemyWave::Tier minTier;
	EnemyWave::Tier maxTier;
	sf::Time minWaveTimeDelay;
	sf::Time maxWaveTimeDelay;
	sf::Time difficultyRate;
	std::vector<std::string> waveIDs;

	//the list containing the waves being used in this level
	std::vector<EnemyWave*> levelWaves;
	//maps an enemy name to the config file path
	std::map<std::string, std::string> enemyNameMap;
	//maps a spawn point name to a position in the world
	std::map<std::string, sf::Vector2f> levelSpawnPoints;
	//enemy wave templates - divided into tiers
	//std::vector<std::map<std::string, EnemyWave>> enemyWaves;
	std::map<std::string, EnemyWave> enemyWaves;

	//this is private as we only want to call this through the load function
	void addEnemyWave(const std::string waveID, sf::Time waveTimeDelay);

	//loads Waves.json and populates the map
	void loadWaves(const std::string filepath);
};

#endif

