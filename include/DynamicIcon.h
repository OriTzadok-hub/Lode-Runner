#pragma once
#include "Icon.h"

enum Direction_t {UP ,DOWN ,RIGHT ,LEFT};
class DynamicIcon : public Icon
{
public:
	DynamicIcon() {};
	~DynamicIcon() {};


	virtual void draw(sf::RenderWindow& window) {}
	virtual void move(float timePassed, sf::Vector2f boardsize){}
	bool outOfBoard(sf::Vector2f size);
	Direction_t getDirection()const;
	sf::Vector2f getStartingPosition()const;
	sf::Vector2f getPosition()const;
	void setStartingPosition(sf::Vector2f pos);
	sf::Vector2f getNextDirection(Direction_t direction)const;
	sf::Vector2f getPrevPos()const;

protected:
	sf::Vector2f getCenter(sf::Vector2f pos)const;
	sf::Vector2f m_startingPosition;
	sf::Vector2f m_prevPos;
	Direction_t m_direction;
};


