#include "Animation.h"

Animation::Animation()
	: numFrames(0)
{

}

Animation::~Animation()
{
	for(it = framePtrs.begin(); it != framePtrs.end(); it++)
	{
		delete *it;
	}
}

void Animation::addFrame(const sf::Time &duration, const sf::IntRect &rect)
{
	framePtrs.push_back(new Frame(duration, rect));
	numFrames++;
}

void Animation::addRow(sf::Vector2i &origin, const unsigned int numFrames, const sf::Vector2i &frameSize, const sf::Time &frameDuration)
{
	for(unsigned int i = 0; i < numFrames; i++)
	{
		sf::IntRect rect(origin, frameSize);
		addFrame(frameDuration, rect);
		origin.x += frameSize.x;
	}
}

Frame *Animation::getFrameAt(unsigned int index) const
{
	if(index < framePtrs.size())
		return framePtrs.at(index);

	return NULL;
}

const unsigned int Animation::getNumFrames() const
{
	return numFrames;
}

