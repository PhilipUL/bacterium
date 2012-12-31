#ifndef ANIMATIONMANAGER_H_
#define ANIMATIONMANAGER_H_

#include "Animation.h"
#include "Entity.h"
#include "PausableClock.h"
#include <SFML/Graphics.hpp>

class AnimationManager
{
public:
	AnimationManager();
	~AnimationManager();

	void setAnimationList(std::map<std::string, Animation*> *animationListPtr);

	void addAnimation(const std::string &animationName, Animation *animation);
	void removeAnimation(const std::string &animationName);

	void playAnimation(Entity &targetPtr, const std::string &animationName, const bool loop = true);
	void setDefaultAnimation(Entity &targetPtr, const std::string &animationName, const bool loop = true);

	void pauseCurrentAnimation();
	void resumeCurrentAnimation();
	void stopCurrentAnimation();

	void Update(Entity &targetPtr);

	void Flush();

private:

	std::map<std::string, Animation*>::const_iterator it;
	std::map<std::string, Animation*> *animationListPtr;

	//animation
	Animation *currentAnimationPtr;
	PausableClock pClock;
	bool onLoop;

	//frames
	unsigned int currentFrameIndex;
	Frame *currentFramePtr;
	void advanceFrame();
	bool onLastFrame();

	void resetCurrentAnimation(Entity &targetPtr);

};

#endif //ANIMATIONMANAGER