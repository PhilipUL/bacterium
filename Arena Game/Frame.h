#ifndef FRAME_H_
#define FRAME_H_

#include <SFML\Graphics.hpp>

struct Frame
{
	Frame(sf::Time duration, sf::IntRect rect)
		: duration(duration), rect(rect)
	{

	}

	sf::Time duration;
	sf::IntRect rect;
};

#endif