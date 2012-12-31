#ifndef ANIMATEDENTITY
#define ANIMATEDENTITY

#include "Entity.h"
#include "IUpdatable.h"
#include "AnimationManager.h"

class AnimatedEntity : public Entity, public IUpdatable
{
public:
	AnimatedEntity();
	~AnimatedEntity();

	virtual void Flush();

	virtual void Update();

	//animation
	virtual void initAnimation(std::map<std::string, Animation*> *animationListPtr);

	virtual void animate(const std::string &name, const bool loop = false);
	void pauseAnimation();
	void resumeAnimation();

protected:
	AnimationManager animationManager;
};

#endif

