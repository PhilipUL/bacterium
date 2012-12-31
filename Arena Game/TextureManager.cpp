#include "TextureManager.h"


TextureManager::TextureManager()
{
}


TextureManager::~TextureManager()
{

}

void TextureManager::loadResource(const std::string filepath)
{
	sf::Texture *texturePtr = new sf::Texture();
	if(texturePtr->loadFromFile(filepath))
	{
		resourceMap[filepath] = texturePtr;
	}
	else
	{
		delete texturePtr;
	}
}
