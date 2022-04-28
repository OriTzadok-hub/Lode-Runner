#include "PlayerStatus.h"

PlayerStatus::PlayerStatus()
{
	m_font = *(FileManager::instance().getFont(INGAME));
	m_statusBar.setFont(m_font);
	m_statusBar.setFillColor(sf::Color::Black);
	m_life.setTexture(*(FileManager::instance().getLifeTexture()));
	
}
//-------------------------------------------------------------
//draws the status of the player on the screen - life,level num ,score
void PlayerStatus::draw(sf::RenderWindow& window, int life, int score, int level, sf::Vector2f BoardSize)
{
	std::string status = "SCORE " + std::to_string(score) +
		"   LEVEL " + std::to_string(level) + "   LIFE  ";
	m_statusBar.setPosition(0, BoardSize.x + 5.f);
	m_statusBar.setString(status);
	m_statusBar.setCharacterSize(P_SIZE);
	window.draw(m_statusBar);
	for (int i = 0; i < life; i++)
	{
		m_life.setPosition(m_statusBar.getGlobalBounds().width + i * P_SIZE, BoardSize.x + 10.f);
		window.draw(m_life);
	}
}
//-------------------------------------------------------------