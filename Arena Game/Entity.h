#ifndef ENTITY_H_
#define ENTITY_H_

#include "IDrawable.h"
#include "EntityTypes.h"
#include "SoundPlayer.h"
#include "ParticleEmitterBuilder.h"

class Entity : public IDrawable
{
public:
	Entity();
	virtual ~Entity();

	void Load(const sf::Texture &texture);
	virtual void Flush();
	virtual void Draw(sf::RenderWindow& window);
	void updateCollisionBox();
	void playHitSound();
	void loadHitEmitter();

	//Setters/Mutators
	void setPos(const sf::Vector2f& position);
	void setRect(const sf::IntRect& collisionBox){Entity::collisionBox = collisionBox;}
	void setActive(const bool val){active = val;}
	void setSpeed(const sf::Vector2f speed){this->speed = speed;}
	void setType(const TYPE type){this->type = type;}
	void setRotation(const float angle) { sprite.setRotation(angle); }
	void setColliding (const bool colliding) {this -> colliding = colliding ;}
	void setScale(const sf::Vector2f scale);
	void setHitSoundFilepath(const std::string &filepath) { this->hitSoundFilepath = filepath; }
	void setHitEmitterFilepath(const std::string &filepath) { this->hitEmitterFilepath = filepath; }

	//Getters/Accessors
	const sf::Vector2f& getPos() const {return sprite.getPosition();}
	const sf::IntRect& getRect() const {return collisionBox;}
	const sf::Sprite& getSprite() const {return sprite;}
	const sf::Vector2f& getSpeed() const {return speed;}
	const TYPE getType() const {return type;}
	const bool isActive() const {return active;}
	const bool isColliding () const {return colliding ;}
	void setFrame(const sf::IntRect&);

protected:
	sf::Sprite sprite;
	sf::IntRect collisionBox;
	sf::Vector2f speed;
	bool active;
	TYPE type;
	std::string hitSoundFilepath;
	std::string hitEmitterFilepath;
	bool colliding;
};

#endif