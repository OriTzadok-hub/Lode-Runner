#include "Ladder.h"
#include "player.h"


Ladder::Ladder(sf::Vector2f pos)
{
	m_sprite.setTexture(*(FileManager::instance().getIconTexture(LADDER)));
	m_sprite.setScale(sf::Vector2f(((float)P_SIZE / m_sprite.getGlobalBounds().height),
		((float)P_SIZE / m_sprite.getGlobalBounds().height)));
	m_pos = pos;
}
//-------------------------------------------------------------
void Ladder::draw(sf::RenderWindow& window, sf::Vector2f pos)
{
	m_sprite.setPosition(pos);
	window.draw(m_sprite);
}
//-------------------------------------------------------------
void Ladder::collide(Player* object)
{
	object->collide(this);
}
//-------------------------------------------------------------
void Ladder::collide(Icon* object)
{
	object->collide(this);
}
//-------------------------------------------------------------
Ladder::~Ladder()
{
}
//-------------------------------------------------------------