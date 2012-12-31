#include "InputHandler.h"

InputHandler::InputHandler()
	: axisThreshold(30.0f)
{
	/*setPrimaryButton(sf::Mouse::Left);
	setTrapButton(sf::Mouse::Right);
	setSpecialKey(sf::Keyboard::Space);
	setMeleeKey(sf::Keyboard::E);

	setMoveUpKey(sf::Keyboard::W);
	setMoveDownKey(sf::Keyboard::S);
	setMoveLeftKey(sf::Keyboard::A);
	setMoveRightKey(sf::Keyboard::D);*/
}

InputHandler::~InputHandler()
{

}

void InputHandler::load(const std::string filepath)
{
	std::filebuf fb;
	fb.open(filepath, std::ios::in);

	Json::Value root;
	Json::Reader reader;
	bool successfulParse = reader.parse(std::istream(&fb), root);
	if(!successfulParse)
	{
		std::cerr << "Unsuccessful parse: " << filepath << std::endl;
		std::cerr << reader.getFormattedErrorMessages() << std::endl;
		return;
	}

	setPrimaryButton(root["primaryAttack"].asUInt());
	setTrapButton(root["trapAttack"].asUInt());
	setSpecialKey(root["specialAttack"].asUInt());
	setMeleeKey(root["meleeAttack"].asUInt());

	setMoveUpKey(root["moveUp"].asUInt());
	setMoveDownKey(root["moveDown"].asUInt());
	setMoveLeftKey(root["moveLeft"].asUInt());
	setMoveRightKey(root["moveRight"].asUInt());
}

void InputHandler::setPrimaryButton(const unsigned int buttonIndex)
{
	if(isValidIndex(buttonIndex, sf::Mouse::ButtonCount))
	{
		this->primaryButton = static_cast<sf::Mouse::Button>(buttonIndex);
	}
}

void InputHandler::setTrapButton(const unsigned int buttonIndex)
{
	if(isValidIndex(buttonIndex, sf::Mouse::ButtonCount))
	{
		this->trapButton = static_cast<sf::Mouse::Button>(buttonIndex);
	}
}

void InputHandler::setSpecialKey(const unsigned int keyIndex)
{
	if(isValidIndex(keyIndex, sf::Keyboard::KeyCount))
	{
		this->specialKey = static_cast<sf::Keyboard::Key>(keyIndex);
	}
}


void InputHandler::setMeleeKey(const unsigned int keyIndex)
{
	if(isValidIndex(keyIndex, sf::Keyboard::KeyCount))
	{
		this->meleeKey = static_cast<sf::Keyboard::Key>(keyIndex);
	}
}

void InputHandler::setMoveUpKey(const unsigned int keyIndex)
{
	if(isValidIndex(keyIndex, sf::Keyboard::KeyCount))
	{
		this->moveUpKey = static_cast<sf::Keyboard::Key>(keyIndex);
	}
}

void InputHandler::setMoveDownKey(const unsigned int keyIndex)
{
	if(isValidIndex(keyIndex, sf::Keyboard::KeyCount))
	{
		this->moveDownKey = static_cast<sf::Keyboard::Key>(keyIndex);
	}
}

void InputHandler::setMoveLeftKey(const unsigned int keyIndex)
{
	if(isValidIndex(keyIndex, sf::Keyboard::KeyCount))
	{
		this->moveLeftKey = static_cast<sf::Keyboard::Key>(keyIndex);
	}
}

void InputHandler::setMoveRightKey(const unsigned int keyIndex)
{
	if(isValidIndex(keyIndex, sf::Keyboard::KeyCount))
	{
		this->moveRightKey = static_cast<sf::Keyboard::Key>(keyIndex);
	}
}

void InputHandler::bigBootyLoop(sf::RenderWindow& window)
{
	sf::Event myEvent;
	while(window.pollEvent(myEvent))
	{
		switch(myEvent.type)
		{
		case sf::Event::Closed:
			window.close();
			break;
		case sf::Event::KeyPressed:
			//if other keys..
			break;
		case sf::Event::MouseButtonPressed:
			if(myEvent.mouseButton.button == sf::Mouse::Left)
			{
				//left button clicked
				//std::cout << "left clicked" << std::endl;
			}
			break;
		case sf::Event::MouseButtonReleased:
			if(myEvent.mouseButton.button == sf::Mouse::Left)
			{
				//left button released
				//std::cout << "left released" << std::endl;
			}
			break;
		default:
			break;

		}
	}
}

void InputHandler::handleInput(Player &player, const sf::RenderWindow& window)
{
	handlePlayerMovement(player);
	getMousePos(window);
}

void InputHandler::handlePlayerMovement(Player &player)
{
	if(joystickNum == -1)
	{
		//up
		if(sf::Keyboard::isKeyPressed(moveUpKey))
		{
			player.move(sf::Vector2f(0, -player.getSpeed().y));
		}
		//down
		else if(sf::Keyboard::isKeyPressed(moveDownKey))
		{
			player.move(sf::Vector2f(0, player.getSpeed().y));
		}
		//left
		if(sf::Keyboard::isKeyPressed(moveLeftKey))
		{
			player.move(sf::Vector2f(-player.getSpeed().x, 0));
		}
		//right
		else if(sf::Keyboard::isKeyPressed(moveRightKey))
		{
			player.move(sf::Vector2f(player.getSpeed().x, 0));
		}
			
	}
	else
	{
		//get the current values of the x and y axis
		float xVal = sf::Joystick::getAxisPosition(joystickNum, sf::Joystick::X);
		float yVal = sf::Joystick::getAxisPosition(joystickNum, sf::Joystick::Y);

		//if they are below the threshold, they might as well be 0
		if(std::abs(xVal) < axisThreshold) 
			xVal = 0;
		if(std::abs(yVal) < axisThreshold)
			yVal = 0;
				
		if(xVal != 0 || yVal != 0)
		{
			player.move(sf::Vector2f(player.getSpeed().x * xVal / 100, player.getSpeed().y * yVal / 100));
		}
	}
}

void InputHandler::handlePlayerAttacks(sf::RenderWindow &window, Player &player)
{
	sf::Vector2f direction;
	if(joystickNum == -1)
	{
		//means the user is not using a joystick, and therefore M+K
		direction = sf::Vector2f(VectorFuncs::intToFloat(sf::Mouse::getPosition(window)) - player.getPos());
		if(sf::Mouse::isButtonPressed(primaryButton))
		{
			player.useAbility(player.getPrimaryAttack(), direction);
		}
		if(sf::Mouse::isButtonPressed(trapButton))
		{
			player.useAbility(player.getTrapAttack(), direction);
		}
		if(sf::Keyboard::isKeyPressed(meleeKey))
		{
			player.useAbility(player.getMeleeAttack(), direction);
		}
		if(sf::Keyboard::isKeyPressed(specialKey))
		{
			player.useAbility(player.getSpecialAttack(), direction);
		}
	}
	else
	{
		direction = sf::Vector2f(sf::Joystick::getAxisPosition(joystickNum, sf::Joystick::U),
			sf::Joystick::getAxisPosition(joystickNum, sf::Joystick::R));
		if(std::abs(direction.x) > 30 || std::abs(direction.y) > 30)
		{
			player.useAbility(player.getPrimaryAttack(), direction);
		}
		if(sf::Joystick::getAxisPosition(joystickNum, sf::Joystick::Z) < -50)
		{
			player.useAbility(player.getSpecialAttack(), direction);
		}
		if(sf::Joystick::getAxisPosition(joystickNum, sf::Joystick::Z) > 50)
		{
			player.useAbility(player.getMeleeAttack(), direction);
		}
		if(sf::Joystick::isButtonPressed(joystickNum, 5))
		{
			player.useAbility(player.getTrapAttack(), direction);
		}
	}
}

sf::Vector2i InputHandler::getMousePos(const sf::RenderWindow& window)
{
	return sf::Mouse::getPosition(window);
}

sf::Vector2i InputHandler::getMouseDirection(const sf::Vector2i v,sf::RenderWindow& window)
{
	return sf::Vector2i((getMousePos(window).x - v.x),(getMousePos(window).y - v.y));
}


bool InputHandler::clicked(sf::RenderWindow &window)
{
	return sf::Mouse::isButtonPressed(sf::Mouse::Left);
}