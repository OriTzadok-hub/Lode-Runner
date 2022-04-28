#pragma once
#include "Enemy.h"

class StaticEnemy : public Enemy
{
public:
	StaticEnemy();
	void move(float timePassed, sf::Vector2f boardSize);
	void changeDirection();
private:
	
};