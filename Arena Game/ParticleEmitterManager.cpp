#include "ParticleEmitterManager.h"


ParticleEmitterManager::ParticleEmitterManager(void)
{
}


ParticleEmitterManager::~ParticleEmitterManager(void)
{
}

void ParticleEmitterManager::addParticleEmitter(ParticleEmitter *particleEmitterPtr)
{
	if(particleEmitterPtr != NULL)
	{
		particleEmitters.push_back(particleEmitterPtr);
	}
}

void ParticleEmitterManager::Update()
{
	for(unsigned int i = 0; i < particleEmitters.size(); i++)
	{
		currentParticleEmitter = particleEmitters.at(i);
		currentParticleEmitter->Update();
		if(!currentParticleEmitter->isActive())
		{
			delete currentParticleEmitter;
			particleEmitters.erase(particleEmitters.begin() + i);
			i--;
		}
	}
}

void ParticleEmitterManager::Draw(sf::RenderWindow &window)
{
	for(it = particleEmitters.begin() ; it != particleEmitters.end(); it++)
	{
		(*it)->Draw(window);
	}
}

void ParticleEmitterManager::Flush()
{
	for(it = particleEmitters.begin() ; it != particleEmitters.end(); it++)
	{
		delete (*it);
	}
	particleEmitters.clear();
}

void ParticleEmitterManager::pause()
{
	for(it = particleEmitters.begin() ; it != particleEmitters.end(); it++)
	{
		(*it)->pause();
	}
}

void ParticleEmitterManager::resume()
{
	for(it = particleEmitters.begin() ; it != particleEmitters.end(); it++)
	{
		(*it)->resume();
	}
}
