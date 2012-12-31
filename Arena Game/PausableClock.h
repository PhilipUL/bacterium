#ifndef PAUSABLECLOCK_H_
#define PAUSABLECLOCK_H_

#include <SFML\System\Clock.hpp>

class PausableClock
{
public:
	PausableClock(bool isPaused = false);
	PausableClock(const PausableClock &pausableClock);
	~PausableClock(void);

	void pause();
	void resume();
	void restart();
	sf::Time getElapsedTime();

private:
	sf::Clock clock;
	sf::Time time;
	bool isPaused;
};

#endif

