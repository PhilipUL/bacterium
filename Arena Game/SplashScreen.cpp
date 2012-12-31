#include "SplashScreen.h"

void SplashScreen::Show(sf::RenderWindow& window, TextureManager &textureManager, InputHandler &input)
{	
	sf::Sprite sprite;
	sprite.setTexture(*textureManager.getResource("Config/Content/Images/Menus/splashScreen.png"));
	sprite.setScale((float)window.getSize().x / sprite.getTexture()->getSize().x, (float)window.getSize().y / sprite.getTexture()->getSize().y);
	sprite.setColor(sf::Color(sprite.getColor().r, sprite.getColor().g, sprite.getColor().b,0));

	fadeIn = true;
	stopSplash = false;

	
	while(true)
	{
		if(input.clicked(window) || stopSplash)
		{
			break;
		}

		window.clear();
		
		if(fadeIn == true)
		{
			fadeSpriteIn(window, sprite);
		}else{
			fadeSpriteOut(window,sprite);
		}
		
		window.draw(sprite);
		window.display();
		
	}
}

void SplashScreen::fadeSpriteIn(sf::RenderWindow & renderWindow, sf::Sprite& sprite) 
{
    if((int)sprite.getColor().a < 255)
	{
		sf::Color color = sprite.getColor();
		color.a++;
		sprite.setColor(color);
	}else{
		fadeIn = false;
	}
}

void SplashScreen::fadeSpriteOut(sf::RenderWindow & renderWindow, sf::Sprite& sprite) 
{
	if(sprite.getColor().a > 0)
	{
		sf::Color color = sprite.getColor();
		color.a--;
		sprite.setColor(color);
	}else{
		stopSplash = true;
	}
}