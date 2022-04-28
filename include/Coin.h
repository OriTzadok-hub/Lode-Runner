#pragma once
#include "StaticIcon.h"


class Player;
class Wall;
class Enemy;
class Level;

class Coin : public StaticIcon
{
public:
	Coin();
	Coin(sf::Vector2f Pos);
	void draw(sf::RenderWindow& window, sf::Vector2f pos);
	
	~Coin();

	virtual void collide(Icon* object);
	virtual void collide(Player* object);
	virtual void collide(Enemy* object) {};
	virtual void collide(Coin* object) {};
	virtual void collide(Wall* object) {};
	virtual void collide(Bar* object) {};
	virtual void collide(SpecialObject* object) {};
	virtual void collide(Ladder* object) {};
	virtual void collide(Hole* object) {};
	

private:
	
	
};


