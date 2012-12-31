#ifndef SPLASHSCREEN_H_
#define SPLASHSCREEN_H_

#include "Global.h"
#include "TextureManager.h"
#include "InputHandler.h"

class SplashScreen
{
public:
	void Show(sf::RenderWindow& window, TextureManager &textureManager, InputHandler &input);
	void fadeSpriteIn(sf::RenderWindow & renderWindow, sf::Sprite& sprite);
	void fadeSpriteOut(sf::RenderWindow & renderWindow, sf::Sprite& sprite);

private:
	bool fadeIn, stopSplash;
};

#endif