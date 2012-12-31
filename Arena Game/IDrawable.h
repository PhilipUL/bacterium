#ifndef IDRAWABLE_H_
#define IDRAWABLE_H_

#include "Global.h"

class IDrawable
{
public:
	virtual void Draw(sf::RenderWindow&) = 0;
};

#endif