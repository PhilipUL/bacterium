#ifndef INPUTHANDLER_H_
#define INPUTHANDLER_H_

#include "Global.h"
#include "Player.h"

//for file reading
#include "json\json.h"
#include <fstream>
//end file reading

class InputHandler
{
public:
	InputHandler();
	~InputHandler();

	void load(const std::string filepath);

	//setters, lots of them!
	void setJoystickNum(const int joystickNum) { this->joystickNum = joystickNum; }
	const int getJoystickNum() { return this->joystickNum; }

	//all these have been overloaded to accept ints aswell. This makes it easier to be read in from a file
	void setPrimaryButton(const sf::Mouse::Button button) { this->primaryButton = button; }
	void setPrimaryButton(const unsigned int buttonIndex);
	void setTrapButton(const sf::Mouse::Button button) { this->trapButton = button; }
	void setTrapButton(const unsigned int buttonIndex);
	void setSpecialKey(const sf::Keyboard::Key key) { this->specialKey = key; }
	void setSpecialKey(const unsigned int keyIndex);
	void setMeleeKey(const sf::Keyboard::Key key) { this->meleeKey = key; }
	void setMeleeKey(const unsigned int keyIndex);

	void setMoveUpKey(const sf::Keyboard::Key key) { this->moveUpKey = key; }
	void setMoveUpKey(const unsigned int keyIndex);
	void setMoveDownKey(const sf::Keyboard::Key key) { this->moveDownKey = key; }
	void setMoveDownKey(const unsigned int keyIndex);
	void setMoveLeftKey(const sf::Keyboard::Key key) { this->moveDownKey = key; }
	void setMoveLeftKey(const unsigned int keyIndex);
	void setMoveRightKey(const sf::Keyboard::Key key) { this->moveDownKey = key; }
	void setMoveRightKey(const unsigned int keyIndex);

	bool isValidIndex(const unsigned int index, const unsigned int count) const { return index < count; }

	//Handles input
	void handleInput(Player &player, const sf::RenderWindow& window);

	//Handles player movement
	void handlePlayerMovement(Player &player);

	//Handles player attacks
	void handlePlayerAttacks(sf::RenderWindow &window, Player &player);

	//Gets the mouse position
	sf::Vector2i getMousePos(const sf::RenderWindow& window);

	//Gets the direction between a vector and a mouse
	sf::Vector2i getMouseDirection(const sf::Vector2i v,sf::RenderWindow& window);

	//Checks to see whether the left mouse button was clicked
	bool clicked(sf::RenderWindow &window);

	//Main loop
	void bigBootyLoop(sf::RenderWindow &window);

private:
	//how can I put these two together?
	//I.E. what if I want the primary key to be on the keyboard and not mouse?
	sf::Mouse::Button primaryButton;
	sf::Mouse::Button trapButton;
	sf::Keyboard::Key specialKey;
	sf::Keyboard::Key meleeKey;

	sf::Keyboard::Key moveUpKey;
	sf::Keyboard::Key moveDownKey;
	sf::Keyboard::Key moveLeftKey;
	sf::Keyboard::Key moveRightKey;

	float axisThreshold;
	int joystickNum;
};
#endif