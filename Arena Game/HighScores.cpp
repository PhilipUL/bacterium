#include "HighScores.h"


HighScores::HighScores(void)
	: maxNumHighScores(10), currentIndex(0), currentScore(0)
{
	resetNameString();

	highScoresText.setPosition(100, 0);
	nameText.setPosition(50, 450);
	scoreText.setPosition(50, 400);

	scores.setPosition(500, 0);
	enterText.setPosition(50, 550);
}


HighScores::~HighScores(void)
{

}

void HighScores::load(const std::string filepath, const sf::Font &font)
{
	this->filepath = filepath;
	std::filebuf fb;
	fb.open(filepath, std::ios::in);

	Json::Value root;
	Json::Reader reader;
	reader.parse(std::istream(&fb), root);

	Json::Value highScoresValue = root["highScores"];
	for(unsigned int i = 0; i < highScoresValue.size(); i++)
	{
		Json::Value highScore = highScoresValue[i];
		highScores.push_back(HighScore(highScore["name"].asString(), highScore["score"].asFloat()));
	}

	//if we have less than 10 highscores, fill the rest with blanks
	if(highScores.size() < maxNumHighScores)
	{
		for(unsigned int i = highScores.size(); i < maxNumHighScores; i++)
		{
			highScores.push_back(HighScore("...", 0));
		}
	}

	highScoresText.setFont(font);
	nameText.setFont(font);
	scoreText.setFont(font);

	scores.setFont(font);
	enterText.setFont(font);

	highScoresText.setString(format());

	scores.setString(formatScores());
	enterText.setString("Press Enter to continue");
}

void HighScores::save()
{
	Json::StyledWriter writer;
	Json::Value root;
	Json::Value highScoresValue(Json::arrayValue);

	for(unsigned int i = 0; i < highScores.size(); i++)
	{
		Json::Value highScore;
		highScore["name"] = highScores.at(i).name;
		highScore["score"] = highScores.at(i).score;

		highScoresValue.append(highScore);
	}
	root["highScores"] = highScoresValue;

	std::ofstream file(filepath);
	file << writer.write(root);
	file.close();
}

void HighScores::update()
{
	if(!isNewHighScore(currentScore))
	{
		return;
	}
	//since we only want to accept certain characters, we must only
	//check when valid keys are pressed. Only accepting capital letters and numbers
	if(currentIndex < MAX_NAME_LENGTH)
	{
		//letters, caps only
		unsigned int start = static_cast<int>(sf::Keyboard::A);
		unsigned int end = static_cast<int>(sf::Keyboard::Z);
		int offset = 'A'; //SFML enum to ascii offset
		for(unsigned int i = start; i <= end; i++)
		{
			if(sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(i)))
			{
				nameString[currentIndex++] = i + offset;
				nameText.setString(updateNameString());
			}
		}

		//numbers
		start = static_cast<int>(sf::Keyboard::Num0);
		end = static_cast<int>(sf::Keyboard::Num9);
		offset = 22;
		for(unsigned int i = start; i <= end; i++)
		{
			if(sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(i)))
			{
				nameString[currentIndex++] = i + offset; //ascii offset
				nameText.setString(updateNameString());
			}
		}

		//numpad numbers
		start = static_cast<int>(sf::Keyboard::Numpad0);
		end = static_cast<int>(sf::Keyboard::Numpad9);
		offset = -27;
		for(unsigned int i = start; i <= end; i++)
		{
			if(sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(i)))
			{
				nameString[currentIndex++] = i + offset; //ascii offset
				nameText.setString(updateNameString());
			}
		}

	}
	if(currentIndex > 0 && sf::Keyboard::isKeyPressed(sf::Keyboard::Back))
	{
		nameString[--currentIndex] = ' ';
		nameText.setString(updateNameString());
	}
}

void HighScores::draw(sf::RenderWindow &window)
{
	window.draw(highScoresText);
	window.draw(scoreText);
	window.draw(nameText);

	window.draw(scores);
	window.draw(enterText);
}

void HighScores::addNewHighScore(const std::string name, const float score)
{
	//to insert in the middle of a vector we need to use an iterator
	for(it = highScores.begin(); it != highScores.end(); it++)
	{
		//find where it belongs
		if(it->score < score)
		{
			//insert it in the correct place (that's what she said)
			highScores.insert(it, HighScore(name, score));
			//get rid of the highscore that was originally the last score on the score board
			highScores.erase(highScores.end() - 1);
			//save the info in memory and in file
			highScoresText.setString(format());

			scores.setString(formatScores());

			save();
			//reset the values for the next one
			resetNameString();
			currentScore = 0;
			currentIndex = 0;
			break;
		}
	}
}

const bool HighScores::isNewHighScore(const float score) const
{
	return score > (highScores.end() - 1)->score;
}

const std::string HighScores::format()
{
	std::stringstream sstream;
	for(unsigned int i = 0; i < highScores.size(); i++)
	{
		//sstream << i+1 <<  ". "<< highScores.at(i).name << "" << std::setw(40 - highScores.at(i).name.size()) << highScores.at(i).score << "\n";
		sstream << i+1 << ". " << highScores.at(i).name << "\n";
	}
	return sstream.str();
}

const std::string HighScores::formatScores()
{
	std::stringstream sstream;
	for(unsigned int i = 0; i < highScores.size(); i++)
	{
		//sstream << i+1 <<  ". "<< highScores.at(i).name << "" << std::setw(40 - highScores.at(i).name.size()) << highScores.at(i).score << "\n";
		sstream << std::fixed << std::setprecision(2) << highScores.at(i).score << "\n";
	}
	return sstream.str();
}

const std::string HighScores::updateNameString()
{
	std::stringstream sstream;
	sstream << "NEW HIGHSCORE!\nENTER NAME: " << nameString;
	return sstream.str();
}

void HighScores::resetNameString()
{
	for(unsigned int i = 0; i < MAX_NAME_LENGTH; i++)
	{
		nameString[i] = ' ';
	}
	nameString[MAX_NAME_LENGTH] = '\0';
	nameText.setString(updateNameString());
}

void HighScores::setCurrentScore(const float score)
{
	this->currentScore = score;
	std::stringstream sstream;
	sstream << "SCORE: " << std::fixed << std::setprecision(2) << currentScore;
	scoreText.setString(sstream.str());

	if(isNewHighScore(score))
	{
		resetNameString();
	}
	else
	{
		nameText.setString("");
	}
}
