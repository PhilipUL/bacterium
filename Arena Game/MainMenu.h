#ifndef MAINMENU_H_
#define MAINMENU_H_

#include "Menu.h"

class MainMenu: public Menu
{
public:

	MainMenu();
	~MainMenu();

	virtual void Load();
	virtual void Draw(sf::RenderWindow& window);
	virtual void Update(sf::RenderWindow& window, InputHandler &input);
	virtual void initMap(sf::RenderWindow& window, TextureManager &textureManager);

	bool isInRect(sf::Vector2i, sf::RectangleShape);
	MenuResult changeScreen(sf::RenderWindow& window, InputHandler &input);

private:
	sf::Sprite backgroundSprite;
	sf::Sprite logoSprite;
	MenuResult menuValue;
	std::map<MenuResult,sf::RectangleShape>::iterator it;
};
#endif