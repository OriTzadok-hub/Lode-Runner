#include "RandomEnemy.h"



RandomEnemy::RandomEnemy()
{
	m_sprite.setTexture(*(FileManager::instance().getIconTexture(ENEMY)));
	//m_sprite.setScale(sf::Vector2f(((float)P_SIZE / m_sprite.getGlobalBounds().height),
		//((float)P_SIZE / m_sprite.getGlobalBounds().height)));
	m_sprite.setOrigin(getCenter(m_sprite.getPosition()));
	SetPosition(m_sprite.getOrigin());
	m_direction = LEFT;
}
//-------------------------------------------------------------
void RandomEnemy::move(float timePassed, sf::Vector2f boardSize)
{
	m_prevPos = m_sprite.getPosition();
	float distance = m_speed * timePassed;
	
	int steps = (rand() % 1000);
	
	if (timePassed > steps || stuck)
	{
		stuck = false;
		switchDirection();
	}

	switch (m_direction)
	{
	case RIGHT:
		m_sprite.move(distance, 0);
		break;
	case LEFT:
		m_sprite.move(-distance, 0);
		break;
	}

	if (outOfBoard(boardSize))
	{
		m_sprite.setPosition(m_prevPos);
		switchDirection();
	}
	m_pos = m_sprite.getPosition();

}
//-------------------------------------------------------------
void RandomEnemy::switchDirection()
{
	if (m_direction == LEFT)
		m_direction = RIGHT;
	else
		m_direction = LEFT;
}
//-------------------------------------------------------------

