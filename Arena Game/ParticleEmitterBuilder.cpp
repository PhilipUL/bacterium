#include "ParticleEmitterBuilder.h"

ParticleEmitterBuilder ParticleEmitterBuilder::singleton = ParticleEmitterBuilder();

ParticleEmitterBuilder::ParticleEmitterBuilder()
{

}

ParticleEmitterBuilder::~ParticleEmitterBuilder()
{

}

ParticleEmitterBuilder *ParticleEmitterBuilder::getInstance()
{
	return &singleton;
}

void ParticleEmitterBuilder::init(ParticleResourceManager *particleResourcePtr, ParticleEmitterManager *particleEmitterManagerPtr)
{
	if(particleResourcePtr != NULL)
	{
		this->particleResourcePtr = particleResourcePtr;
	}
	if(particleEmitterManagerPtr != NULL)
	{
		this->particleEmitterManagerPtr = particleEmitterManagerPtr;
	}
}

void ParticleEmitterBuilder::release()
{
	
}

ParticleEmitter *ParticleEmitterBuilder::buildParticleEmitter(const std::string filepath, const sf::Vector2f &position)
{
	//since the basic entity does not contain any dynamically allocated memory (pointers),
	//we can use the default copy constructor
	const ParticleEmitter *templatePtr = particleResourcePtr->getResource(filepath);
	if(templatePtr == NULL)
	{
		return NULL;
	}

	ParticleEmitter *particleEmitterPtr = new ParticleEmitter(*templatePtr);
	particleEmitterPtr->setPosition(position);
	particleEmitterPtr->load();
	particleEmitterPtr->setActive(true);

	particleEmitterManagerPtr->addParticleEmitter(particleEmitterPtr);

	return particleEmitterPtr;
}
