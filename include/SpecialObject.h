#pragma once
#include "StaticIcon.h"

class Player;
class Coin;
class Enemy;
class Level;
class Wall;
class Bar;

const int NUM_OF_SPECIALS = 4;
enum Special_t{LIFE,SCORE,TIME,ADD_ENEMY};

class SpecialObject : public StaticIcon
{
public:
	SpecialObject(sf::Vector2f pos);
	Special_t getSpecial()const;

	virtual void collide(Icon* object);
	virtual void collide(Player* object);
	virtual void collide(Enemy* object) {};
	virtual void collide(Coin* object) {};
	virtual void collide(Wall* object) {};
	virtual void collide(Bar* object) {};
	virtual void collide(SpecialObject* object) {};
	virtual void collide(Ladder* object) {};
	virtual void collide(Hole* object) {};

	void draw(sf::RenderWindow& window, sf::Vector2f pos);
	
private:
	Special_t m_special;
	

};