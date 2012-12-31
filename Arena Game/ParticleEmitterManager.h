#ifndef PARTICLEEMITTERMANAGER_H_
#define PARTICLEEMITTERMANAGER_H_

#include "SFML\Graphics.hpp"
#include "ParticleEmitter.h"

class ParticleEmitterManager
{
public:
	ParticleEmitterManager(void);
	~ParticleEmitterManager(void);

	void addParticleEmitter(ParticleEmitter *particleEmitterPtr);

	void Update();
	void Draw(sf::RenderWindow &window);
	void Flush();

	void pause();
	void resume();

private:
	std::vector<ParticleEmitter*> particleEmitters;
	std::vector<ParticleEmitter*>::const_iterator it;

	//for iterating through the update
	ParticleEmitter *currentParticleEmitter;

};

#endif
