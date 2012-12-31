#include "World.h"

World::World()
{	
	
}


World::~World()
{
	flush();
}

void World::init(TextureManager &textureManager, SoundManager &soundManager)
{
	entityResourceManager.init(textureManager, soundManager);
	EntityBuilder::getInstance()->init(&entityResourceManager, &entityManager);
	particleResourceManager.init(textureManager);
	ParticleEmitterBuilder::getInstance()->init(&particleResourceManager, &particleEmitterManager);

	//do this to prevent crash on exit
	EntityBuilder::getInstance()->buildPlayer("Config/Entities/Characters/Player.json", sf::Vector2f(400, 300));
	entityManager.Flush();
}

void World::Update(sf::RenderWindow& window)
{
	if(getPlayers()->empty())
	{
		playerLoseClock.resume();
	}
	else
	{
		hud.Update();
		worldScore = hud.getDisplayScore();
	}

	enemySpawnManager.Update(*getPlayers());
	entityManager.Update(window);
	particleEmitterManager.Update();
}

void World::Load(const std::string filepath, sf::RenderWindow &window, TextureManager &textureManager, FontManager &fontManager)
{

	//open up the file
	std::filebuf fb;
	fb.open(filepath, std::ios::in);

	//try to parse it
	Json::Value root;
	Json::Reader reader;
	bool parseSuccessful = reader.parse(std::istream(&fb), root);
	if(!parseSuccessful)
	{
		std::cerr << "Unsuccessful parse" << filepath << std::endl;
		std::cerr << reader.getFormattedErrorMessages() << std::endl;
		return;
	}
	//now we have it parsed we can close it
	fb.close();

	//set the background
	std::string backgroundFilepath = root.get("background", "").asString();
	if(!backgroundFilepath.empty())
	{
		worldSprite.setTexture(*textureManager.getResource(backgroundFilepath));
		worldSprite.setScale((float)window.getSize().x / worldSprite.getTexture()->getSize().x, (float)window.getSize().y / worldSprite.getTexture()->getSize().y);
	}

	//build the walls
	Json::Value walls = root["walls"];
	for(unsigned int i = 0; i < walls.size(); i++)
	{
		Json::Value wall = walls[i];
		std::string filepath = wall["name"].asString();
		sf::Vector2f position(wall["position"]["x"].asFloat(), wall["position"]["y"].asFloat());
		EntityBuilder::getInstance()->buildEntity(filepath, position);
	}

	//build the player
	EntityBuilder::getInstance()->buildPlayer("Config/Entities/Characters/Player.json", sf::Vector2f(400, 300));
	
	//set level mode, normal or survival
	mode = (Mode) root.get("mode", NORMAL).asInt();

	//build hud
	Json::Value hudValue = root.get("hud", NULL);
	const sf::Texture *healthBarPtr = textureManager.getResource(hudValue.get("healthBar", NULL).asString());
	const sf::Texture *healthBarBackgroundPtr = textureManager.getResource(hudValue.get("healthBarBackground", NULL).asString());
	hud.init(*healthBarPtr, *healthBarBackgroundPtr, entityManager.getVector(PLAYER), fontManager, mode);
	
	//load the enemy waves, mode is important
	enemySpawnManager.load(root, &entityManager, mode);

	playerLoseClock.pause();
	playerLoseClock.restart();
}

void World::flush()
{
	entityResourceManager.Flush();
	entityManager.Flush();
	enemySpawnManager.flush();
	EntityBuilder::getInstance()->release();
	particleResourceManager.Flush();
	ParticleEmitterBuilder::getInstance()->release();
	particleEmitterManager.Flush();
	hud.Flush();
}

void World::Draw(sf::RenderWindow &window)
{
	window.draw(worldSprite);
	entityManager.Draw(window);
	particleEmitterManager.Draw(window);
	hud.Draw(window);
}

const std::vector<Entity*> *World::getPlayers()
{
	return entityManager.getVector(PLAYER);
}

const bool World::isOver()
{
	if(enemySpawnManager.hasPlayerWon())
	{
		//Player beat level
		std::cout << "YOU WIN" << std::endl;
		return true;
	}
	else if(playerLoseClock.getElapsedTime() >= sf::milliseconds(1000))
	{
		//Game Over, player dead
		std::cout << "YOU LOSE" << std::endl;
		return true;
	}
	return false;
}

void World::updateWorldScore()
{
	float prevWorldScore = worldScore;
	worldScore = 0;
	for(unsigned int i = 0; i < getPlayers()->size(); i++)
	{
		worldScore += dynamic_cast<Player*>(getPlayers()->at(i))->getScore();
	}
	if(worldScore == 0)
	{
		worldScore = prevWorldScore;
	}
}
