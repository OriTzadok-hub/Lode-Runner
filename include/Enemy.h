#pragma once
#include "DynamicIcon.h"
#include <time.h>



class Enemy : public DynamicIcon
{
public:
	Enemy() {};

	virtual void move(float timePassed, sf::Vector2f boardSize) {};
	void draw(sf::RenderWindow &window);
	void SetPosition(sf::Vector2f new_pos);
	Direction_t getDirection()const;
	void setStuck();

	virtual void collide(Icon* object) {};
	virtual void collide(Player* object) {};
	virtual void collide(Enemy* object) {};
	virtual void collide(Coin* object) {};
	virtual void collide(Wall* object);
	virtual void collide(Bar* object) {};
	virtual void collide(SpecialObject* object) {};
	virtual void collide(Ladder* object) {};
	virtual void collide(Hole* object) {};

protected:
	float m_speed = 25;
	bool stuck = false;
	

};


