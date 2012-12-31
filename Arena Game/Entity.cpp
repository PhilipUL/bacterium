#include "Entity.h"

Entity::Entity()
	: active(true), colliding(false)
{

}

Entity::~Entity()
{

}

void Entity::Flush()
{
	
}

void Entity::Load(const sf::Texture &texture)
{
	sprite.setTexture(texture);
	sprite.setOrigin((float)texture.getSize().x / 2, (float)texture.getSize().y / 2);
	updateCollisionBox();
}


void Entity::Draw(sf::RenderWindow& window)
{
	window.draw(sprite);

	/*sf::RectangleShape shape;
	int width = sprite.getTextureRect().width * sprite.getScale().x;
	int height = sprite.getTextureRect().height * sprite.getScale().y;
	shape.setPosition((int)getPos().x - width / 2, (int)getPos().y - height / 2);
	shape.setSize(sf::Vector2f(collisionBox.width, collisionBox.height));
	shape.setOutlineThickness(2.0f);
	shape.setOutlineColor(sf::Color::Black);
	shape.setFillColor(sf::Color::Transparent);
	window.draw(shape);*/
}

void Entity::setFrame(const sf::IntRect &rect)
{
	//set the texture rectangle in the sprite sheet
	sprite.setTextureRect(rect);
	sprite.setOrigin((float)rect.width / 2, (float)rect.height / 2);
	updateCollisionBox();


	//sprite.setScale(0.5, 0.5);
}

void Entity::setPos(const sf::Vector2f& position)
{
	sprite.setPosition(position);
	updateCollisionBox();
}

void Entity::setScale(const sf::Vector2f scale)
{
	sprite.setScale(scale);
	updateCollisionBox();
}

void Entity::updateCollisionBox()
{
	int width = int(sprite.getTextureRect().width * sprite.getScale().x);
	int height = int(sprite.getTextureRect().height * sprite.getScale().y);
	collisionBox = sf::IntRect((int)getPos().x - width / 2, (int)getPos().y - height / 2, width, height);
}

void Entity::playHitSound()
{
	if(!hitSoundFilepath.empty())
	{
		SoundPlayer::getInstance()->playSound(hitSoundFilepath);
	}
}

void Entity::loadHitEmitter()
{
	if(!hitEmitterFilepath.empty())
	{
		ParticleEmitterBuilder::getInstance()->buildParticleEmitter(hitEmitterFilepath, this->getPos());
	}
}





