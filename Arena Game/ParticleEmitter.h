#ifndef PARTICLEEMITER_H_
#define PARTICLEEMITER_H_

#include "Particle.h"

class ParticleEmitter
{
public:
	ParticleEmitter();
	~ParticleEmitter();

	const sf::Vector2f &getPosition () const { return position	;}
	const unsigned int  getNum      () const { return num		;}
	const bool          getExplode  () const { return explode	;}
	const bool			isActive	() const { return active	;}

	void setPosition (const sf::Vector2f &position) { this -> position = position ;}
	void setNum      (int          num     ) { this -> num      = num      ;}
	void setExplode  (bool         explode ) { this -> explode  = explode  ;}

	//ryans code
	void setParticleTexture(const sf::Texture *texturePtr) { this->particleTexturePtr = texturePtr; }
	void setMinLifeTime(const sf::Time &lifeTime) { this->minLifeTime = lifeTime; }
	void setMaxLifeTime(const sf::Time &lifeTime) { this->maxLifeTime = lifeTime; }
	void setSpeed(const sf::Vector2f &speed) { this->speed = speed; }
	void setActive(const bool active) { this->active = active; }

	void load();
	void Update()                         ;
	void Draw  (sf::RenderWindow& window) ;

	void pause();
	void resume();

private:

	Particle* generateNewParticle();

	vector<Particle*> particles ;

	sf::Vector2f position ;
	unsigned int num      ;
	bool         explode  ;

	//ryans code
	const sf::Texture *particleTexturePtr;
	sf::Time minLifeTime;
	sf::Time maxLifeTime;
	sf::Vector2f speed;
	bool active;

};
#endif
