#include "PausableClock.h"


PausableClock::PausableClock(bool isPaused)
	: isPaused(isPaused), time(sf::milliseconds(0))
{
	clock = sf::Clock();
}

PausableClock::PausableClock(const PausableClock &pausableClock)
{
	this->clock = sf::Clock();
	this->time = sf::milliseconds(0);
	this->isPaused = pausableClock.isPaused;
}

PausableClock::~PausableClock(void)
{

}

void PausableClock::pause()
{
	//if not already paused
	if(!isPaused)
	{
		isPaused = true;
		time += clock.getElapsedTime();
	}
}

void PausableClock::resume()
{
	//can only resume if already paused
	if(isPaused)
	{
		isPaused = false;
		clock.restart();
	}
}

void PausableClock::restart()
{
	time = sf::milliseconds(0);
	clock.restart();
}

sf::Time PausableClock::getElapsedTime()
{
	if(!isPaused)
		return time + clock.getElapsedTime();
	else
		return time;
}