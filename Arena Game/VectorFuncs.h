/*
*
*Static class does not require object creation
*
*/

#ifndef VECTOR_FUNCS_H_
#define VECTOR_FUNCS_H_

#include <SFML\Graphics.hpp>
#include <math.h>

#define PI 3.14159265

class VectorFuncs
{
public:

	/*
	*Returns the length of the given vector
	*/
	static inline float length(sf::Vector2f v)
	{
		return ( sqrt ( (v.x) * (v.x) + (v.y) * (v.y) ) );
	}


	/*
	*Transforms the length of the given vector to one
	*/
	static inline sf::Vector2f normalise(sf::Vector2f v)
	{
		return sf::Vector2f( v.x / length(v) , v.y / length(v) );
	}


	/*
	*Converts a Vector2f to a Vector2i
	*/
	static inline sf::Vector2i floatToInt(sf::Vector2f v)
	{
		return sf::Vector2i( (int)v.x , (int)v.y );
	}


	/*
	*Converts a Vector2i to a Vector2f
	*/
	static inline sf::Vector2f intToFloat(sf::Vector2i v)
	{
		return sf::Vector2f( (float)v.x , (float)v.y );
	}


	/*
	*Multiplies two vectors together 
	*/
	static inline sf::Vector2f mult(sf::Vector2f v1, sf::Vector2f v2)
	{
		return sf::Vector2f( v1.x * v2.x , v1.y * v2.y );
	}


	/*
	*Returns the distance between two given Vectors
	*To pass in  two Vector2i just use the floatToInt 
	*function
	*/
	static inline float distance(sf::Vector2f v1,sf::Vector2f v2)
	{
		return sqrt( (v1.x - v2.x) * (v1.x - v2.x) + (v1.y - v2.y) * (v1.y - v2.y)); 
	}


	/*
	*Rotates a vector around a point through a given 
	*angle
	*/
	static inline sf::Vector2f rotate(sf::Vector2f v1, float angle)
	{
		return sf::Vector2f( (float)(v1.x*cos(angle*PI/180)) - (float)(v1.y*sin(angle*PI/180)) , (float)(v1.y*cos(angle*PI/180)) + (float)(v1.x*sin(angle*PI/180)) );
	}

	/*
	*Returns the direction between two given directions
	*/
	static inline sf::Vector2f getDirection(sf::Vector2f v1,sf::Vector2f v2)
	{
		return sf::Vector2f(v2.x - v1.x , v2.y - v1.y);
	}

	static inline double getAngle(sf::Vector2f &v)
	{
		return atan2(v.x, v.y) * 180 / PI;
	}
};
#endif