#ifndef MENU_H_
#define MENU_H_

#include "Global.h"
#include "InputHandler.h"
#include "TextureManager.h"

class Menu
{
public:
	Menu();
	virtual ~Menu();

	static const enum MenuResult {PLAY, EXIT, HIGHSCORES, CREDITS, BACK,NOTHING};

	virtual void Load() = 0;
	virtual void Draw(sf::RenderWindow& window) = 0;
	virtual void Update(sf::RenderWindow& window, InputHandler &input) = 0;

	virtual void initMap(sf::RenderWindow &window, TextureManager &textureManager) = 0;
	
	const sf::Sprite& getSprite() const {return sprite;}

protected:
	sf::Sprite sprite;

	std::map<MenuResult, sf::RectangleShape> menuItems;

private:
};

#endif