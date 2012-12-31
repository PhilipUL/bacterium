#include "AnimationManager.h"

AnimationManager::AnimationManager()
	: onLoop(true), currentFrameIndex(0)
{
	
}

AnimationManager::~AnimationManager()
{
	
}

void AnimationManager::setAnimationList(std::map<std::string, Animation*> *animationListPtr)
{
	if(animationListPtr != NULL)
	{
		//if(&animationList != NULL)
		//{
		//	//flush the old list
		//	Flush();
		//}
		this->animationListPtr = animationListPtr;

		///////HARDCODED PLZZZ FIX///////////////
		currentAnimationPtr = animationListPtr->begin()->second;
		currentFramePtr = currentAnimationPtr->getFrameAt(0);
		///////////////////////////////////////////
	}
}

void AnimationManager::addAnimation(const std::string &animationName, Animation *animation)
{
	if(animation != NULL)
		(*animationListPtr)[animationName] = animation;
}

void AnimationManager::removeAnimation(const std::string &animationName)
{
	//only remove the animation if we find it in the list
	if(animationListPtr->find(animationName) != animationListPtr->end())
	{
		animationListPtr->erase(animationName);
		delete (*animationListPtr)[animationName];
	}
}

void AnimationManager::playAnimation(Entity &targetPtr, const std::string &animationName, const bool loop)
{
	//only play the animation if it exists in the map
	if(animationListPtr->find(animationName) != animationListPtr->end())
	{
		//sometimes, they might want to play the same animation but change the loop state
		if(onLoop != loop)
			onLoop = loop;

		//if it's not already playing
		if(currentAnimationPtr != (*animationListPtr)[animationName])
		{
			onLoop = loop;
			currentAnimationPtr = (*animationListPtr)[animationName];
			resetCurrentAnimation(targetPtr);
			pClock.restart();
		}
	}
}

void AnimationManager::setDefaultAnimation(Entity &targetPtr, const std::string &animationName, const bool loop)
{
	onLoop = loop;
	currentAnimationPtr = (*animationListPtr)[animationName];
	resetCurrentAnimation(targetPtr);
}

void AnimationManager::pauseCurrentAnimation()
{
	pClock.pause();
}

void AnimationManager::resumeCurrentAnimation()
{
	pClock.resume();
}

void AnimationManager::stopCurrentAnimation()
{
	//will we need a default animation variable?
}

void AnimationManager::Update(Entity &targetPtr)
{
	//if it's time to move onto the next frame
	//check if we still need to animate or stop
	if(!onLastFrame() || onLoop)
	{
		if(pClock.getElapsedTime() >= currentFramePtr->duration)
		{
			advanceFrame();
			targetPtr.setFrame(currentFramePtr->rect);
			pClock.restart();
		}
	}
}

void AnimationManager::resetCurrentAnimation(Entity &targetPtr)
{
	currentFrameIndex = 0;
	currentFramePtr = currentAnimationPtr->getFrameAt(currentFrameIndex);
	targetPtr.setFrame(currentFramePtr->rect);
}

void AnimationManager::advanceFrame()
{
	if(onLastFrame())
		currentFrameIndex = 0;
	else
		currentFrameIndex++;

	currentFramePtr = currentAnimationPtr->getFrameAt(currentFrameIndex);
}

bool AnimationManager::onLastFrame()
{
	if(currentAnimationPtr != NULL)
	{
		return currentFrameIndex == currentAnimationPtr->getNumFrames() - 1;
	}
	else
	{
		return false;
	}
}

void AnimationManager::Flush()
{
	for(it = animationListPtr->begin(); it != animationListPtr->end(); it++)
	{
		delete it->second;
	}
	animationListPtr->clear();
	delete animationListPtr;
}