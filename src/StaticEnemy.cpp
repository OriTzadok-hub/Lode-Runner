#include "StaticEnemy.h"


StaticEnemy::StaticEnemy()
{
	m_sprite.setTexture(*(FileManager::instance().getIconTexture(ENEMY)));
	//m_sprite.setScale(sf::Vector2f(((float)P_SIZE / m_sprite.getGlobalBounds().height),
		//((float)P_SIZE / m_sprite.getGlobalBounds().height)));
	m_sprite.setOrigin(getCenter(m_sprite.getPosition()));
	SetPosition(m_sprite.getOrigin());
	m_direction = LEFT;
}
//-------------------------------------------------------------
void StaticEnemy::move(float timePassed, sf::Vector2f boardSize)
{
	m_prevPos = m_sprite.getPosition();
	float distance = m_speed * timePassed;
	

	switch (m_direction)
	{
	case RIGHT:
		m_sprite.move(distance, 0);
		break;
	case LEFT:
		m_sprite.move(-distance, 0);
		break;
	}

	if (outOfBoard(boardSize)||stuck)
	{
		m_sprite.setPosition(m_prevPos);
		changeDirection();
		if (stuck)
			stuck = false;
	}
	m_pos = m_sprite.getPosition();
}
//-------------------------------------------------------------
void StaticEnemy::changeDirection()
{
	if(m_direction == LEFT)
		m_direction = RIGHT;
	else 
		m_direction = LEFT;
}
//-------------------------------------------------------------