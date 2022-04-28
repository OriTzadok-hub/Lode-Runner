#include "Bar.h"
#include "Player.h"


Bar::Bar(sf::Vector2f pos)
{
	m_sprite.setTexture(*(FileManager::instance().getIconTexture(BAR)));
	m_sprite.setScale(sf::Vector2f(((float)P_SIZE / m_sprite.getGlobalBounds().height),
		((float)P_SIZE / m_sprite.getGlobalBounds().height)));
	m_pos = pos;

}
//-------------------------------------------------------------

void Bar::draw(sf::RenderWindow& window, sf::Vector2f pos)
{
	m_sprite.setPosition(pos);
	window.draw(m_sprite);
}
//-------------------------------------------------------------
Bar::~Bar()
{
}
//-------------------------------------------------------------
void Bar::collide(Icon* object)
{
	object->collide(this);
}
//-------------------------------------------------------------
void Bar::collide(Player* object)
{
	object->collide(this);
}