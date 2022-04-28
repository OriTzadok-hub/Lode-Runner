#include "Coin.h"

#include "Player.h"
#include "Enemy.h"
#include "Wall.h"

Coin::Coin(sf::Vector2f pos)
{
	m_pos = pos;
	m_sprite.setTexture(*(FileManager::instance().getIconTexture(COIN)));
	m_sprite.setScale(sf::Vector2f(((float)P_SIZE / m_sprite.getGlobalBounds().height),
		((float)P_SIZE / m_sprite.getGlobalBounds().height)));
}
//-------------------------------------------------------------
void Coin::draw(sf::RenderWindow& window, sf::Vector2f pos)
{
	m_sprite.setPosition(pos);
	window.draw(m_sprite);
}

//-------------------------------------------------------------
Coin::~Coin()
{
}
//-------------------------------------------------------------
void Coin::collide(Icon* object)
{
	object->collide(this);
}
//-------------------------------------------------------------
void Coin::collide(Player* object)
{
	m_pos = sf::Vector2f(-1, -1);
	
}





