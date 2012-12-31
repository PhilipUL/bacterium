#include "HUD.h"
#include "World.h"

HUD::HUD()
{

}

HUD::~HUD()
{
	Flush();
}

void HUD::init(const sf::Texture &healthBar, const sf::Texture &healthBarBackground, const std::vector<Entity*> *players, FontManager &fontManager, int mode)
{
	scoreText.setFont(*fontManager.getResource("Config/Content/Fonts/calibri.ttf"));
	scoreText.setPosition(20,40);
	scoreText.setColor(sf::Color::Black);
	this->mode = mode;

	for(unsigned int i = 0; i < players->size(); i++)
	{
		Player *playerPtr = dynamic_cast<Player*>(players->at(i)) ;

		if(playerPtr != NULL)
		{
			this->players.push_back(playerPtr);

			healthRecs.push_back(HealthBars(sf::RectangleShape(sf::Vector2f((float)healthBar.getSize().x, (float)healthBar.getSize().y)),
				sf::RectangleShape(sf::Vector2f((float)healthBarBackground.getSize().x, (float)healthBarBackground.getSize().y))));

			healthRecs.at(i).healthBar.setTexture(&healthBar);
			healthRecs.at(i).healthBarBackground.setTexture(&healthBarBackground);

			//hardcoded
			healthRecs.at(i).healthBar.setPosition(15, 15);
			healthRecs.at(i).healthBarBackground.setPosition(10, 10);

			/*healthRecs.push_back(sf::RectangleShape(this->players->at(i)->getPlayerBars().health.getSize()));
			healthRecs.at(i).setTexture(this->players->at(i)->getPlayerBars().health.getTexture());
			healthRecs.at(i).setTextureRect(this->players->at(i)->getPlayerBars().health.getTextureRect());*/
		}
	}

	pClock.restart();
}

void HUD::Draw(sf::RenderWindow& window)
{
	for(unsigned int i = 0; i < healthRecs.size(); i++)
	{
		window.draw(healthRecs.at(i).healthBarBackground);
		window.draw(healthRecs.at(i).healthBar);
	}
	window.draw(scoreText);
}

void HUD::Update()
{
	for(unsigned int i = 0; i < healthRecs.size(); i++)
	{
		healthRecs.at(i).healthBar.setTextureRect(sf::IntRect(0, 0, int((players.at(i)->getHealth() / players.at(i)->getMaxHealth()) * healthRecs.at(i).healthBar.getSize().x), (int)healthRecs.at(i).healthBar.getSize().y));
		healthRecs.at(i).healthBar.setScale( (players.at(i)->getHealth() / players.at(i)->getMaxHealth()), 1.0f);

		sstream.str("");
		sstream << "Score: ";
		if(mode == World::NORMAL)
		{
			displayScore = players.at(0)->getScore();
			sstream << displayScore;
		}
		else if(mode == World::SURVIVAL)
		{
			int scoreInMillis = pClock.getElapsedTime().asMilliseconds();
			//round to 2 decimal places
			displayScore = std::floorf(scoreInMillis / 10 + 0.5) / 100;
			//display score with exactly 2 decimal places (e.g. 2.20 instead of 2.2)
			sstream << std::fixed << std::setprecision(2) << displayScore << "s";
		}
		scoreText.setString(sstream.str());
	}
}

void HUD::Flush()
{
	players.clear();
	healthRecs.clear();
}