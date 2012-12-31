#ifndef PARTICLE_H_
#define PARTICLE_H_

#include "Global.h"
#include "PausableClock.h"

class Particle
{
public:
	Particle(void);
	~Particle(void);

	const sf::Vector2f &getPos             () const { return sprite.getPosition() ;}
	const sf::Vector2f &getVelocity        () const { return velocity             ;}
	const float        getAngle            () const { return angle                ;}
	const float        getAngularVelocity  () const { return angularVelocity      ;}

	void setPos              (sf::Vector2f &position) { sprite.setPosition(position)              ;}
	void setVelocity         (sf::Vector2f &velocity) { this -> velocity        = velocity        ;}
	void setAngle            (float angle)            { this -> angle           = angle           ;}
	void setAngularVelocity  (float angularVelocity)  { this -> angularVelocity = angularVelocity ;}


	void Update ()                         ;
	void Draw   (sf::RenderWindow& window) ;

	//ryans code
	void setLifeTime(const sf::Time &lifeTime) { this->lifeTime = lifeTime; }
	const bool isActive() const { return active; }
	void setTexture(const sf::Texture &texture) { sprite.setTexture(texture); }

	void pause() { pClock.pause(); }
	void resume() { pClock.resume(); }

private:
	sf::Sprite   sprite          ;
	sf::Vector2f velocity        ;
	float        angle           ;
	float        angularVelocity ;

	//ryan's code
	PausableClock pClock;
	sf::Time lifeTime;
	bool active;


};
#endif
