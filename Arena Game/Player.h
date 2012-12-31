#ifndef PLAYER_H_
#define PLAYER_H_

#include "character.h"

class Player : public Character
{
public:
	Player();
	~Player();

	virtual void move(sf::Vector2f &movement);
	virtual void onHit(Entity *entityPtr);

	void setScore(const float score) { this->score = score; }
	void addToScore(const float score) { this->score += score; }
	const float getScore() const { return score; }

	void setPrimaryAttack(const unsigned int index) { this->primaryAttackIndex = index; }
	void setMeleeAttack(const unsigned int index) { this->meleeAttackIndex = index; }
	void setSpecialAttack(const unsigned int index) { this->specialAttackIndex = index; }
	void setTrapAttack(const unsigned int index) { this->trapAttackIndex = index; }

	const unsigned int getPrimaryAttack() const { return primaryAttackIndex; }
	const unsigned int getMeleeAttack() const { return meleeAttackIndex; }
	const unsigned int getSpecialAttack() const { return specialAttackIndex; }
	const unsigned int getTrapAttack() const { return trapAttackIndex; }

private:
	float score;

	int primaryAttackIndex;
	int meleeAttackIndex;
	int specialAttackIndex;
	int trapAttackIndex;
};
#endif
