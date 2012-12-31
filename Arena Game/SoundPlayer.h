#ifndef SOUNDPLAYER_H_
#define SOUNDPLAYER_H_

#include "SoundManager.h"

class SoundPlayer
{

public:

	static SoundPlayer *getInstance();

	void init(SoundManager *soundManagerPtr);
	void release();

	void playSound(const std::string filepath);

	//test
	void Update();

private:
	SoundPlayer(void);
	~SoundPlayer(void);

	static SoundPlayer singleton;

	SoundManager *soundManagerPtr;



	//test
	std::vector<sf::Sound*> currentlyPlayingSounds;
};

#endif

