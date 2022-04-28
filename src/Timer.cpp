#pragma once
#include "Timer.h"
#include "Level.h"



Timer::Timer()
{
	m_font = *(FileManager::instance().getFont(INGAME));
	m_timerText.setFont(m_font);
	m_timerText.setCharacterSize(P_SIZE);
	m_timerText.setFillColor(sf::Color::Black);
	m_clockSprite.setTexture(*(FileManager::instance().getClockTexture()));
}
//-------------------------------------------------------------
int Timer::getTimer() const
{
	return m_timerInt;
}
//-------------------------------------------------------------
void Timer::setTimer(const int time)
{
	m_clock.restart(); //start the timer
	m_timerInt = time;
}
//-------------------------------------------------------------
void Timer::addTime()
{
	m_timerInt += 10;
}
//-------------------------------------------------------------
bool Timer::ifPastSecond()
{
	sf::Time timePassed = m_clock.getElapsedTime();
	if (timePassed.asSeconds() > 1)
	{
		m_clock.restart();
		return true;
	}
	return false;
}
//-------------------------------------------------------------
void Timer::updateTimer()
{
	if (ifPastSecond())
		m_timerInt--;
}
//-------------------------------------------------------------
bool Timer::ifEndTime() const
{

	if (m_timerInt == 0)
		return true;
	return false;
}
//-------------------------------------------------------------
Timer& Timer::instance()
{
	static Timer timer;
	return timer;
}
//-------------------------------------------------------------
void Timer::draw(sf::RenderWindow& window)
{
	m_clockSprite.setPosition(0, m_height);
	m_timerText.setString(std::to_string(m_timerInt));
	m_timerText.setPosition(m_clockSprite.getGlobalBounds().width +5.f , m_height);
	window.draw(m_clockSprite);
	window.draw(m_timerText);
}
//-------------------------------------------------------------
void Timer::getBoardSize(sf::Vector2f size)
{
	int m_width = size.x;
	int m_height = size.y;
}
//-------------------------------------------------------------