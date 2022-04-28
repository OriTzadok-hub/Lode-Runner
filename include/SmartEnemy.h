#pragma once
#include "Enemy.h"

class SmartEnemy : public Enemy
{
public:
	SmartEnemy() ;
	void move(float timePassed, sf::Vector2f boardSize);
};


