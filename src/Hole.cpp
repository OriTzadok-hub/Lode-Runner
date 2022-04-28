#include "Hole.h"
#include "Player.h"

Hole::Hole(sf::Vector2f pos)
{
	m_sprite.setTexture(*(FileManager::instance().getIconTexture(HOLE)));
	m_sprite.setScale(sf::Vector2f(((float)P_SIZE / m_sprite.getGlobalBounds().height),
		((float)P_SIZE / m_sprite.getGlobalBounds().height)));
	
		sf::Vector2f fixed(pos.x, pos.y - 3.f);
		m_pos = fixed;
	
}
//-------------------------------------------------------------
void Hole::draw(sf::RenderWindow& window)
{
	m_sprite.setPosition(m_pos);
	window.draw(m_sprite);
}
//-------------------------------------------------------------
Hole::~Hole()
{
}
//-------------------------------------------------------------
void Hole::collide(Icon* object)
{
	object->collide(this);
}
//-------------------------------------------------------------
void Hole::collide(Player* object)
{
	object->collide(this);
}
//-------------------------------------------------------------
