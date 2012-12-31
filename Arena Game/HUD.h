#ifndef HUD_H_
#define HUD_H_

#include "Global.h"
#include "Player.h"
#include "FontManager.h"
#include <sstream>
#include <math.h>
#include <iomanip>

class HUD
{
public:
	HUD();
	~HUD();

	void init(const sf::Texture &healthBar, const sf::Texture &healthBarBackground, const std::vector<Entity*> *players, FontManager &fontManager, int mode);
	void Draw(sf::RenderWindow& window);
	void Update();
	void Flush();

	const float getDisplayScore() const { return displayScore; } 

private:

	struct HealthBars
	{
		HealthBars(sf::RectangleShape healthBar, sf::RectangleShape healthBarBackground)
			: healthBar(healthBar), healthBarBackground(healthBarBackground)
		{

		}

		sf::RectangleShape healthBar;
		sf::RectangleShape healthBarBackground;
	};

	std::vector<Player*> players;
	std::vector<HealthBars> healthRecs;
	sf::Font scoreFont;
	sf::Text scoreText;
	std::stringstream sstream;
	PausableClock pClock;
	int mode;
	float displayScore;
};

#endif