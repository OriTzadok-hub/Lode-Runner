#pragma once
#include "Icon.h"


class StaticIcon : public Icon
{
public:
	StaticIcon() {};
	virtual void draw(sf::RenderWindow &window, sf::Vector2f pos) {}
	~StaticIcon() {};
	sf::Vector2f getPosition()const
	{
		return m_pos;
	}
	void setPosition(sf::Vector2f pos)
	{
		m_pos = pos;
	}


	
};


