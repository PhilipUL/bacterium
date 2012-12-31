#include "SoundManager.h"


SoundManager::SoundManager(void)
{
}


SoundManager::~SoundManager(void)
{
}

void SoundManager::loadResource(const std::string filepath)
{
	sf::SoundBuffer *soundBufferPtr = new sf::SoundBuffer();
	if(soundBufferPtr->loadFromFile(filepath))
	{
		resourceMap[filepath] = soundBufferPtr;
	}
	else
	{
		delete soundBufferPtr;
	}
}
