#include "SpecialObject.h"
#include "Player.h"

SpecialObject::SpecialObject(sf::Vector2f pos)
{
	m_pos = pos;
	m_sprite.setTexture(*(FileManager::instance().getIconTexture(SPECIAL)));
	m_sprite.setScale(sf::Vector2f(((float)P_SIZE / m_sprite.getGlobalBounds().height),
		((float)P_SIZE / m_sprite.getGlobalBounds().height)));

	Special_t specials[] = { LIFE,SCORE,TIME,ADD_ENEMY };
	m_special = specials[rand() % 4];//randomizes the special object type
	
}
//-------------------------------------------------------------
Special_t SpecialObject::getSpecial()const
{
	return m_special;
}
//-------------------------------------------------------------
void SpecialObject::collide(Icon* object)
{
	object->collide(this);
}
//-------------------------------------------------------------
void SpecialObject::collide(Player* object)
{
	m_pos = sf::Vector2f(-1, -1);
	
}
//-------------------------------------------------------------
void SpecialObject::draw(sf::RenderWindow& window, sf::Vector2f pos)
{
	m_sprite.setPosition(pos);
	window.draw(m_sprite);
}
//-------------------------------------------------------------