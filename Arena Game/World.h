#ifndef WORLD_H_
#define WORLD_H_

#include "Global.h"
#include "EntityManager.h"
#include "EnemySpawnManager.h"
#include "EntityBuilder.h"
#include "HUD.h"
#include "TextureManager.h"
#include "FontManager.h"
#include "EntityResourceManager.h"
#include "ParticleEmitterManager.h"
#include "ParticleResourceManager.h"
#include "ParticleEmitterBuilder.h"

class World
{
public:
	World();
	~World(void);

	static const enum Mode { NORMAL, SURVIVAL };

	//Updates
	void Update(sf::RenderWindow& window);

	void init(TextureManager &textureManager, SoundManager &soundManager);
	//Loads entities into the world
	void Load(const std::string filepath, sf::RenderWindow &window, TextureManager &textureManager, FontManager &fontManager);

	void flush();

	//Draws everything in the world
	void Draw(sf::RenderWindow& window);

	//Melee attack ////////////////////TEST/////////////////
	void attack(sf::RenderWindow& window);

	//Returns the player vector
	const std::vector<Entity*> *getPlayers();

	//returns true if the world is over, whether it be by all players dieing,
	//all defeating all waves
	const bool isOver();

	//gets the score of all the players combined
	const float getWorldScore() const { return worldScore; }

private:
	void updateWorldScore();

	EntityManager    entityManager;
	sf::Sprite       worldSprite;
	EnemySpawnManager enemySpawnManager;
	EntityResourceManager entityResourceManager;
	HUD hud;
	ParticleEmitterManager particleEmitterManager;
	ParticleResourceManager particleResourceManager;
	float worldScore;
	PausableClock playerLoseClock;
	Mode mode;
};

#endif
