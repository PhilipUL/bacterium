#include "ParticleResourceManager.h"


ParticleResourceManager::ParticleResourceManager(void)
{
}


ParticleResourceManager::~ParticleResourceManager(void)
{
}

void ParticleResourceManager::init(TextureManager &textureManager)
{
	this->textureManagerPtr = &textureManager;
}

void ParticleResourceManager::loadResource(const std::string filepath)
{
		//open up the file
	std::filebuf fb;
	fb.open(filepath, std::ios::in);

	//try to parse it
	Json::Value root;
	Json::Reader reader;
	bool parseSuccessful = reader.parse(std::istream(&fb), root);
	//now we have it parsed we can close it
	fb.close();

	if(!parseSuccessful)
	{
		std::cerr << "Unable to load particle emitter: " << filepath << std::endl;
		std::cerr << reader.getFormattedErrorMessages() << std::endl;
		return;
	}

	ParticleEmitter *particleEmitterPtr = new ParticleEmitter();

	int numParticles = root.get("numParticles", 1).asInt();
	particleEmitterPtr->setNum(numParticles);

	std::string particleTexture = root.get("particleTexture", "").asString();
	if(!particleTexture.empty())
	{
		particleEmitterPtr->setParticleTexture(textureManagerPtr->getResource(particleTexture));
	}

	Json::Value speed = root.get("speed", NULL);
	particleEmitterPtr->setSpeed(speed == NULL ? sf::Vector2f() : sf::Vector2f(speed["x"].asFloat(), speed["y"].asFloat()));

	Json::Value lifeTime = root.get("lifeTime", NULL);
	particleEmitterPtr->setMinLifeTime(sf::milliseconds(lifeTime["min"].asInt()));
	particleEmitterPtr->setMaxLifeTime(sf::milliseconds(lifeTime["max"].asInt()));

	//not sure about this one...
	bool explode = root.get("explode", false).asBool();
	particleEmitterPtr->setExplode(explode);

	particleEmitterPtr->setActive(false);

	resourceMap[filepath] = particleEmitterPtr;
}
