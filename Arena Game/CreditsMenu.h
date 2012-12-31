#ifndef CREDITSMENU_H_
#define CREDITSMENU_H_

#include "Menu.h"

class CreditsMenu: public Menu
{
public:

	CreditsMenu();
	~CreditsMenu();

	virtual void Load();
	virtual void Draw(sf::RenderWindow& window);
	virtual void Update(sf::RenderWindow& window, InputHandler &input);
	virtual void initMap(sf::RenderWindow& window, TextureManager &textureManager);

	bool isInRect(sf::Vector2i, sf::RectangleShape);
	MenuResult changeScreen(sf::RenderWindow& window, InputHandler &input);

private:
	sf::Sprite backgroundSprite;
	MenuResult menuValue;
	std::map<MenuResult,sf::RectangleShape>::iterator it;
};
#endif