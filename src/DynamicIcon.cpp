#include "DynamicIcon.h"



Direction_t DynamicIcon::getDirection()const
{
	return m_direction;
}
//-------------------------------------------------------------
sf::Vector2f DynamicIcon::getStartingPosition()const
{
	return m_startingPosition;
}
//-------------------------------------------------------------

sf::Vector2f DynamicIcon::getPosition()const
{
	return m_sprite.getPosition();
}
//-------------------------------------------------------------


void DynamicIcon::setStartingPosition(sf::Vector2f pos)
{
	m_startingPosition = pos;
}
//-------------------------------------------------------------
bool DynamicIcon::outOfBoard(sf::Vector2f size)
{
	int distance = P_SIZE / 2;
	return m_sprite.getPosition().x + distance > size.y || m_sprite.getPosition().y + distance > size.x ||
		m_sprite.getPosition().x - distance < 0 || m_sprite.getPosition().y - distance < 0;
}
//-------------------------------------------------------------
sf::Vector2f DynamicIcon::getCenter(sf::Vector2f pos)const
{
	sf::Vector2f newPos;
	newPos.x = (pos.x - ((int)pos.x % P_SIZE)) + P_SIZE / 2;
	newPos.y = (pos.y - ((int)pos.y % P_SIZE)) + P_SIZE / 2;
	return newPos;
}
//-------------------------------------------------------------
//get the next direction position on the screen
sf::Vector2f DynamicIcon::getNextDirection(Direction_t direction)const
{
	sf::Vector2f nextPos = m_sprite.getPosition();

	switch (direction)
	{
	case UP:
		return sf::Vector2f(nextPos.x, nextPos.y - (P_SIZE / 2));
	case DOWN:
		return sf::Vector2f(nextPos.x, nextPos.y + (P_SIZE / 2));
	case RIGHT:
		return sf::Vector2f(nextPos.x + (P_SIZE / 2), nextPos.y);
	case LEFT:
		return sf::Vector2f(nextPos.x - (P_SIZE / 2), nextPos.y);
	}
}
//-------------------------------------------------------------
sf::Vector2f DynamicIcon::getPrevPos()const
{
	return m_prevPos;
}
//-------------------------------------------------------------
