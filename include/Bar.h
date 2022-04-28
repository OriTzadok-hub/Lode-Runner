#pragma once
#include "StaticIcon.h"

class Player;
class Coin;
class Enemy;
class Level;
class Wall;

class Bar: public StaticIcon
{
public:
	Bar(sf::Vector2f pos);
	void draw(sf::RenderWindow& window, sf::Vector2f pos);
	~Bar();
	virtual void collide(Icon* object);
	virtual void collide(Player* object);
	virtual void collide(Enemy* object) {};
	virtual void collide(Bar* object) {};
	virtual void collide(Coin* object) {};
	virtual void collide(Wall* object) {};
	virtual void collide(SpecialObject* object) {};
	virtual void collide(Ladder* object) {};
	virtual void collide(Hole* object) {};

private:

};