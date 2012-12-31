#include "SoundPlayer.h"

#include <iostream>

SoundPlayer SoundPlayer::singleton = SoundPlayer();

SoundPlayer::SoundPlayer(void)
{
}


SoundPlayer::~SoundPlayer(void)
{
	for(unsigned int i = 0; i < currentlyPlayingSounds.size(); i++)
	{
		delete currentlyPlayingSounds.at(i);
	}
}

SoundPlayer *SoundPlayer::getInstance()
{
	return &singleton;
}

void SoundPlayer::init(SoundManager *soundManagerPtr)
{
	this->soundManagerPtr = soundManagerPtr;
}

void SoundPlayer::release()
{

}

void SoundPlayer::playSound(const std::string filepath)
{
	sf::Sound *soundPtr = new sf::Sound(*soundManagerPtr->getResource(filepath));
	if(soundPtr->getBuffer() != NULL)
	{
		currentlyPlayingSounds.push_back(soundPtr);
		soundPtr->play();
	}
}

void SoundPlayer::Update()
{
	for(unsigned int i = 0; i < currentlyPlayingSounds.size(); i++)
	{
		if(currentlyPlayingSounds.at(i)->getStatus() == sf::Sound::Stopped)
		{
			delete currentlyPlayingSounds.at(i);
			currentlyPlayingSounds.erase(currentlyPlayingSounds.begin() + i);
			i--;
		}
	}
}