#include "Particle.h"


Particle::Particle(void)
	: angle(0)
{
	
}


Particle::~Particle(void)
{
}

void Particle::Update()
{
	setPos(getPos() + velocity)   ;
	angle += angularVelocity      ;

	if(pClock.getElapsedTime() >= lifeTime)
	{
		active = false;
	}
}


void Particle::Draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}