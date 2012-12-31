#ifndef HIGHSCORES_H_
#define HIGHSCORES_H_

#include <vector>
#include <sstream>
#include <iomanip>
#include "SFML\Graphics.hpp"

//for file reading
#include "json\json.h"
#include <fstream>
//end file reading

class HighScores
{
public:
	HighScores();
	~HighScores();

	void load(const std::string filepath, const sf::Font &font);
	void save();
	void update();
	void draw(sf::RenderWindow &window);

	void addNewHighScore(const std::string name, const float score);
	const bool isNewHighScore(const float score) const;
	void resetNameString();

	void setCurrentScore(const float score);

	const char* getCurrentName() const { return nameString; }
	const float getCurrentScore() const { return currentScore; }

private:

	struct HighScore
	{
		HighScore(const std::string name, const float score)
			: name(name), score(score)
		{
		}

		std::string name;
		float score;
	};
	const std::string format();
	const std::string updateNameString();


	const unsigned int maxNumHighScores;
	std::vector<HighScore> highScores;
	std::vector<HighScore>::const_iterator it;
	sf::Text highScoresText;
	//we need to save the filepath as we have to write back to the same file later if we add new high scores
	std::string filepath;

	sf::Text nameText;
	sf::Text scoreText;
	static const unsigned int MAX_NAME_LENGTH = 15;
	char nameString[MAX_NAME_LENGTH+1]; //+ 1 to allow room for null terminator
	unsigned int currentIndex;
	float currentScore;

	/////////OPEN DAY//////////
	sf::Text scores;
	const std::string formatScores();
	sf::Text enterText;
	//////////////////////
};

#endif

