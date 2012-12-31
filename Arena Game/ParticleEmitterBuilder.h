#ifndef PARTICLEEMITTERBUILDER_H_
#define PARTICLEEMITTERBUILDER_H_

#include <string>
#include <SFML\Graphics.hpp>

#include "ParticleEmitter.h"
#include "ParticleEmitterManager.h"
#include "ParticleResourceManager.h"

class ParticleEmitterBuilder
{
public:
	
	static ParticleEmitterBuilder *getInstance();

	void init(ParticleResourceManager *particleResourcePtr, ParticleEmitterManager *particleEmitterManagerPtr);
	void release();

	ParticleEmitter *buildParticleEmitter(const std::string filepath, const sf::Vector2f &position);

private:
	ParticleEmitterBuilder();
	~ParticleEmitterBuilder();

	static ParticleEmitterBuilder singleton;

	ParticleResourceManager *particleResourcePtr;
	ParticleEmitterManager *particleEmitterManagerPtr;
};

#endif

