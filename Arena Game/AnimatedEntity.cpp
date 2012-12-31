#include "AnimatedEntity.h"


AnimatedEntity::AnimatedEntity()
{
}


AnimatedEntity::~AnimatedEntity()
{
	
}

void AnimatedEntity::Flush()
{
	animationManager.Flush();
	Entity::Flush();
}

void AnimatedEntity::Update()
{
	animationManager.Update(*this);
}

void AnimatedEntity::animate(const std::string &name, const bool loop)
{
	animationManager.playAnimation(*this, name, loop);
}

void AnimatedEntity::pauseAnimation()
{
	animationManager.pauseCurrentAnimation();
}

void AnimatedEntity::resumeAnimation()
{
	animationManager.resumeCurrentAnimation();
}

void AnimatedEntity::initAnimation(std::map<std::string, Animation*> *animationListPtr)
{
	animationManager.setAnimationList(animationListPtr);
}

