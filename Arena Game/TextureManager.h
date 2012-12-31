#ifndef TEXTUREMANAGER_H_
#define TEXTUREMANAGER_H_

#include "GameResourceManager.h"
#include "SFML\Graphics\Texture.hpp"

class TextureManager : public GameResourceManager<sf::Texture>
{
public:
	TextureManager();
	~TextureManager();

	virtual void loadResource(const std::string filepath);
};

#endif

