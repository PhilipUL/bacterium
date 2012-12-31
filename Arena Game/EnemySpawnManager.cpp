#include "EnemySpawnManager.h"
#include "World.h"


EnemySpawnManager::EnemySpawnManager()
{
}


EnemySpawnManager::~EnemySpawnManager()
{
	flush();
}

void EnemySpawnManager::load(const Json::Value &root, EntityManager *entityManagerPtr, int mode)
{
	this->entityManagerPtr = entityManagerPtr;
	this->mode = mode;
	index = 0;
	playerWon = false;

	loadWaves("Config/Levels/Waves.json");

	if(mode == World::NORMAL)
	{
		modeClock.pause();
		Json::Value waves = root["enemyWaves"];
		for(unsigned int i = 0; i < waves.size(); i++)
		{
			Json::Value wave = waves[i];
			const std::string waveID = wave["waveID"].asString();
			const sf::Time waveTimeDelay = sf::milliseconds(wave.get("waveTimeDelay", 0).asInt());
			addEnemyWave(waveID, waveTimeDelay);
		}
		if(levelWaves.size() > 0)
		{
			waveTimeDelay = levelWaves[0]->getWaveTimeDelay();
		}
		else
		{
			std::cerr << "No waves added to level" << std::endl;
		}
	}
	else if(mode == World::SURVIVAL)
	{
		Json::Value survival = root["survival"];	
		minTier = (EnemyWave::Tier) survival.get("minTier", EnemyWave::VERY_EASY).asInt();
		maxTier = (EnemyWave::Tier) survival.get("maxTier", EnemyWave::MEDIUM).asInt();
		//if the developer is trying to break my parser...
		if(minTier > maxTier)
		{
			EnemyWave::Tier temp = minTier;
			minTier = maxTier;
			maxTier = temp;
		}
		minWaveTimeDelay = sf::milliseconds(survival.get("minWaveTimeDelay", 2000).asInt());
		maxWaveTimeDelay = sf::milliseconds(survival.get("maxWaveTimeDelay", 4000).asInt());
		if(minWaveTimeDelay > maxWaveTimeDelay)
		{
			sf::Time temp = minWaveTimeDelay;
			minWaveTimeDelay = maxWaveTimeDelay;
			maxWaveTimeDelay = temp;
		}
		//if no difficulty rate is set in the config file, the initial min and max tier and wave time delay will never change
		difficultyRate = sf::milliseconds(survival.get("difficultyRate", -1).asInt());
		//pick very first wave time delay (random between min and max)
		int newWaveTimeDelayInMillis = (rand() % (maxWaveTimeDelay - minWaveTimeDelay).asMilliseconds() + minWaveTimeDelay.asMilliseconds());
		waveTimeDelay = sf::milliseconds(newWaveTimeDelayInMillis);
	}
	waveClock.restart();
	modeClock.restart();
}

void EnemySpawnManager::loadWaves(const std::string filepath)
{
	std::filebuf fb;
	fb.open(filepath, std::ios::in);

	Json::Value root;
	Json::Reader reader;
	bool successfulParse = reader.parse(std::istream(&fb), root);
	if(!successfulParse)
	{
		std::cerr << "Unsuccessful parse: " << filepath << std::endl;
		std::cerr << reader.getFormattedErrorMessages() << std::endl;
		return;
	}

	Json::Value nameMap = root["nameMap"];
	for(unsigned int i = 0; i < nameMap.size(); i++)
	{
		std::string name = nameMap[i]["name"].asString();
		std::string filepath = nameMap[i]["filepath"].asString();
		enemyNameMap[name] = filepath;
	}

	Json::Value spawnPoints = root["spawnPoints"];
	for(unsigned int i = 0; i < spawnPoints.size(); i++)
	{
		Json::Value spawnPoint = spawnPoints[i];
		std::string name = spawnPoint["name"].asString();
		float x = spawnPoint["x"].asFloat();
		float y = spawnPoint["y"].asFloat();
		levelSpawnPoints[name] = sf::Vector2f(x, y);
	}

	Json::Value waves = root["waves"];
	for(unsigned int i = 0; i < waves.size(); i++)
	{
		Json::Value wave = waves[i];
		EnemyWave enemyWave;

		EnemyWave::Tier tier = (EnemyWave::Tier) wave.get("tier", EnemyWave::MEDIUM).asInt();
		int spawnTimeDelay = wave.get("spawnTimeDelay", 0).asInt();
		
		enemyWave.setTier(tier);
		enemyWave.setSpawnTimeDelay(sf::milliseconds(spawnTimeDelay));

		Json::Value enemies = wave["enemies"];
		for(unsigned int j = 0; j < enemies.size(); j++)
		{
			std::string name = enemies[j]["name"].asString();
			std::string spawnPoint = enemies[j]["spawnPoint"].asString();;
			enemyWave.addEnemy(enemyNameMap[name], levelSpawnPoints[spawnPoint]);
		}
		std::string waveID = wave["id"].asString();
		enemyWave.setID(waveID);
		enemyWaves[waveID] = enemyWave;
		waveIDs.push_back(waveID);
	}
}

void EnemySpawnManager::addEnemyWave(const std::string waveID, sf::Time waveTimeDelay)
{
	std::map<std::string, EnemyWave>::const_iterator it = enemyWaves.find(waveID);
	if (it != enemyWaves.end())
	{
		EnemyWave *enemyWavePtr = new EnemyWave(it->second);
		enemyWavePtr->setWaveTimeDelay(waveTimeDelay);
		levelWaves.push_back(enemyWavePtr);
	}
	else
	{
		std::cerr << "Wave " << waveID << " does not exist" << std::endl;
	}
}

void EnemySpawnManager::Update(const std::vector<Entity*> &targets)
{
	if(mode == World::NORMAL)
	{
		if(modeClock.getElapsedTime() >= sf::milliseconds(1000))
		{
			playerWon = true;
		}
		if(spawnedAllWaves() && entityManagerPtr->getVector(ENEMY)->empty())
		{
			modeClock.resume();
		}
		for(unsigned int i = 0; i < levelWaves.size(); i++)
		{
			//if time to begin next wave
			if(!spawnedAllWaves() && waveClock.getElapsedTime() >= waveTimeDelay)
			{
				//activate current wave
				levelWaves[index++]->activate();

				if (!spawnedAllWaves())
				{
					//move on to next wave and get the time delay
					waveTimeDelay = levelWaves[index]->getWaveTimeDelay();
					waveClock.restart();
				}
			}

			if(levelWaves[i]->isActive())
			{
				levelWaves[i]->Update(targets);
			}
		}
	}
	else if(mode == World::SURVIVAL)
	{
		//pick random wave and wave time delay, add to levelWaves, activate straight away
		if(waveClock.getElapsedTime() >= waveTimeDelay)
		{
			//randomly pick a wave from the enemyWaves list (key = wave ID)
			std::string waveID = waveIDs[rand() % waveIDs.size()];
			//if wave tier is acceptable, add to levelWaves
			EnemyWave *enemyWavePtr = &enemyWaves[waveID];
			while(enemyWavePtr->getTier() < minTier || enemyWavePtr->getTier() > maxTier)
			{
				waveID = waveIDs[rand() % waveIDs.size()];
				enemyWavePtr = &enemyWaves[waveID];
			}
			//acceptable enemy wave, create new from template
			enemyWavePtr = new EnemyWave(*enemyWavePtr);
			enemyWavePtr->activate();
			std::cout << "activating a wave of " << enemyWavePtr->getID() << std::endl;
			levelWaves.push_back(enemyWavePtr);
			waveClock.restart();

			//pick next wave time delay (random between min and max)
			int newWaveTimeDelayInMillis = (rand() % (maxWaveTimeDelay - minWaveTimeDelay).asMilliseconds() + minWaveTimeDelay.asMilliseconds());
			waveTimeDelay = sf::milliseconds(newWaveTimeDelayInMillis);
			std::cout << "new wtd " << newWaveTimeDelayInMillis << std::endl;
		}

		//increase difficulty as time goes on 
		if(difficultyRate > sf::milliseconds(0) && modeClock.getElapsedTime() >= difficultyRate)
		{
			if(minTier < EnemyWave::VERY_HARD)
			{
				minTier = (EnemyWave::Tier) (minTier + 1);
			}
			if(maxTier < EnemyWave::VERY_HARD)
			{
				maxTier = (EnemyWave::Tier) (maxTier + 1);
			}
			if(minWaveTimeDelay > sf::milliseconds(600))
			{
				minWaveTimeDelay -= sf::milliseconds(500);
			}
			if(maxWaveTimeDelay > sf::milliseconds(1100))
			{
				maxWaveTimeDelay -= sf::milliseconds(500);
			}
			modeClock.restart();
		}

		for(unsigned int i = 0; i < levelWaves.size(); i++)
		{
			if(levelWaves[i]->isActive())
			{
				levelWaves[i]->Update(targets);
			}
			else
			{
				delete levelWaves[i];
				levelWaves.erase(levelWaves.begin() + i);
				i--;
			}
		}
	}
}

void EnemySpawnManager::pause()
{
	waveClock.pause();
	modeClock.pause();
	for(unsigned int i = 0; i < levelWaves.size(); i++)
	{
		levelWaves[i]->pause();
	}
}

void EnemySpawnManager::resume()
{
	waveClock.resume();
	modeClock.resume();
	for(unsigned int i = 0; i < levelWaves.size(); i++)
	{
		levelWaves[i]->resume();
	}
}

void EnemySpawnManager::restart()
{
	waveClock.restart();
	modeClock.restart();
	index = 0;
	for(unsigned int i = 0; i < levelWaves.size(); i++)
	{
		levelWaves[i]->deactivate();
	}
}

void EnemySpawnManager::flush()
{
	for(unsigned int i = 0; i < levelWaves.size(); i++)
	{
		delete levelWaves[i];
	}
	levelWaves.clear();
	enemyNameMap.clear();
	levelSpawnPoints.clear();
	enemyWaves.clear();
}
