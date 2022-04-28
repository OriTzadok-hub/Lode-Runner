#include "Wall.h"
#include "Player.h"
#include "Enemy.h"



Wall::Wall(sf::Vector2f pos)
{
	m_sprite.setTexture(*(FileManager::instance().getIconTexture(WALL)));
	m_sprite.setScale(sf::Vector2f(((float)P_SIZE / m_sprite.getGlobalBounds().height),
		((float)P_SIZE / m_sprite.getGlobalBounds().height)));
	m_pos = pos;
}
//-------------------------------------------------------------
void Wall::draw(sf::RenderWindow & window, sf::Vector2f pos)
{
	m_sprite.setPosition(pos);
	window.draw(m_sprite);
}
//-------------------------------------------------------------
Wall::~Wall()
{
}
//-------------------------------------------------------------
void Wall::collide(Enemy* object)
{
	object->collide(this);
}
//-------------------------------------------------------------
void Wall::collide(Player* object)
{
	object->collide(this);
}
//-------------------------------------------------------------
void Wall::collide(Icon* object)
{
	object->collide(this);
}
//-------------------------------------------------------------

