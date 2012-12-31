#include "ParticleEmitter.h"


ParticleEmitter::ParticleEmitter()
{
	//setting rand seed is now done when we load a world
	//srand((unsigned int)time(NULL));
}


ParticleEmitter::~ParticleEmitter()
{
	//just make sure all particles are deleted
	if(!particles.empty())
	{
		for(unsigned int i = 0; i < particles.size() ; i++)
		{
			delete particles.at(i);
		}
	}
}

void ParticleEmitter::load()
{
	//this should be called after num is set!
	for(unsigned int i = 0; i < num ; i++)
	{
		Particle *particlePtr = generateNewParticle();
		if(particlePtr != NULL)
		{
			particles.push_back(particlePtr);
		}
	}
}

void ParticleEmitter::Update()
{	
	//if no particles are left, this emitter is done
	if(particles.empty())
	{
		active = false;
		return;
	}

	for(unsigned int particle = 0 ; particle < particles.size() ; particle++)
	{
		particles[particle]->Update();
		if(!particles[particle]->isActive())
		{
			delete particles[particle];
			particles.erase(particles.begin() + particle);
			particle--;
		}
	}
}



void ParticleEmitter::Draw(sf::RenderWindow& window)
{
	for(unsigned int i = 0 ; i < particles.size() ; i++)
	{
		particles[i] -> Draw(window) ;
	}
}

void ParticleEmitter::pause()
{
	for(unsigned int i = 0 ; i < particles.size() ; i++)
	{
		particles[i]->pause();
	}
}

void ParticleEmitter::resume()
{
	for(unsigned int i = 0 ; i < particles.size() ; i++)
	{
		particles[i]->resume();
	}
}

Particle* ParticleEmitter::generateNewParticle()
{
	try
	{
		float x = 1.f * (float)((float)rand()/((float)RAND_MAX/ speed.x) * 2 - 1);
		float y = 1.f * (float)((float)rand()/((float)RAND_MAX/ speed.y) * 2 - 1);
		
		if(explode)
		{
			if(rand() % 2 != 0)
				x= -x;
			if(rand()% 2 != 0)
				y = -y;
		}

		sf::Vector2f velocity = sf::Vector2f(x,y);                                                 ;
		float angularVelocity = 0.1f * (float)(rand()/((float)RAND_MAX/100) * 2 - 1) ;

		Particle* particle = new Particle             ;
		particle->setPos(this->position)              ; 
		particle->setVelocity(velocity)               ;
		particle->setAngularVelocity(angularVelocity) ;

		int lifeTime = (rand() % (maxLifeTime - minLifeTime).asMilliseconds()) + minLifeTime.asMilliseconds();
		particle->setLifeTime(sf::milliseconds(lifeTime));
		particle->setTexture(*particleTexturePtr);

		return particle ;
	}
	catch(...)
	{
		return NULL;
	}
}