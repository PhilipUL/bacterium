#include "MainMenu.h"

MainMenu::MainMenu()
{

}

MainMenu::~MainMenu()
{

}

void MainMenu::initMap(sf::RenderWindow &window, TextureManager &textureManager)
{
	//hardcoded positions

	backgroundSprite.setTexture(*textureManager.getResource("Config/Content/Images/Backgrounds/background.png"));

	logoSprite.setTexture(*textureManager.getResource("Config/Content/Images/Menus/gameLogo.png"));
	logoSprite.setPosition(float(window.getSize().x) / 2 - logoSprite.getTextureRect().width / 2, 10);

	sf::RectangleShape playButton;
	playButton.setSize(sf::Vector2f(120.0f, 50.0f));
	playButton.setTexture(textureManager.getResource("Config/Content/Images/Menus/playButton.png"));
	playButton.setPosition(window.getSize().x / 2 - playButton.getSize().x / 2, 300);

	sf::RectangleShape creditsButton;
	creditsButton.setSize(sf::Vector2f(240.0f, 50.0f));
	creditsButton.setTexture(textureManager.getResource("Config/Content/Images/Menus/creditsButton.png"));
	creditsButton.setPosition(window.getSize().x / 2 - creditsButton.getSize().x / 2, 375);

	sf::RectangleShape highScoresButton;
	highScoresButton.setSize(sf::Vector2f(370.0f,50.0f));
	highScoresButton.setTexture(textureManager.getResource("Config/Content/Images/Menus/highScoresButton.png"));
	highScoresButton.setPosition(window.getSize().x / 2 - highScoresButton.getSize().x / 2, 450);

	sf::RectangleShape exitButton;
	exitButton.setSize(sf::Vector2f(120.0f,50.0f));
	exitButton.setTexture(textureManager.getResource("Config/Content/Images/Menus/quitButton.png"));
	exitButton.setPosition(window.getSize().x / 2 - exitButton.getSize().x / 2, 525);

	menuItems[PLAY] = playButton;
	menuItems[CREDITS] = creditsButton;
	menuItems[HIGHSCORES] = highScoresButton;
	menuItems[EXIT] = exitButton;
}

void MainMenu::Load()
{
	
}

void MainMenu::Update(sf::RenderWindow& window, InputHandler &input)
{
	for(it = menuItems.begin(); it != menuItems.end(); it++)
	{
		if(isInRect(input.getMousePos(window),it->second) &&  input.clicked(window))
		{
			menuValue = it->first;
			break;
		}
	}
}

void MainMenu::Draw(sf::RenderWindow& window)
{
	window.draw(backgroundSprite);
	window.draw(logoSprite);
	for(it = menuItems.begin(); it != menuItems.end(); it++)
	{
		window.draw(it->second);
	}
}

bool MainMenu::isInRect(sf::Vector2i position, sf::RectangleShape menuItemRect)
{
	return(menuItemRect.getPosition().y < position.y && 
			menuItemRect.getPosition().y + menuItemRect.getSize().y > position.y &&
			menuItemRect.getPosition().x < position.x &&
			menuItemRect.getPosition().x + menuItemRect.getSize().x > position.x);
}

Menu::MenuResult MainMenu::changeScreen(sf::RenderWindow& window, InputHandler &input)
{
	menuValue = NOTHING;
	Update(window, input);
	return menuValue;
}