#include "Enemy.h"
#include "Player.h"
#include "Coin.h"
#include "Wall.h"



void Enemy::SetPosition(sf::Vector2f new_pos)
{
	m_sprite.setPosition(new_pos);
}
//-------------------------------------------------------------
Direction_t Enemy::getDirection()const
{
	return m_direction;
}
//-------------------------------------------------------------
void Enemy::setStuck()
{
	if (stuck)
		stuck = false;
	else
		stuck = true;
}
//-------------------------------------------------------------
void Enemy::collide(Wall* object)
{
	m_sprite.setPosition(m_prevPos);
	stuck = true;
}
//-------------------------------------------------------------
void Enemy::draw(sf::RenderWindow & window)
{
	window.draw(m_sprite);
}
//-------------------------------------------------------------

