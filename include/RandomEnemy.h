#pragma once
#include "Enemy.h"

class RandomEnemy : public Enemy
{
public:
	RandomEnemy();
	~RandomEnemy() {};
	void switchDirection();
	void move(float timePassed, sf::Vector2f boardSize);
private:
	

};


