#ifndef SOUNDMANAGER_H_
#define SOUNDMANAGER_H_

#include "GameResourceManager.h"
#include "SFML\Audio.hpp"

/*
Use .wav for sound effects, .ogg for music, I think...
*/

class SoundManager : public GameResourceManager<sf::SoundBuffer>
{
public:
	SoundManager();
	~SoundManager();

	virtual void loadResource(const std::string filepath);
};

#endif

