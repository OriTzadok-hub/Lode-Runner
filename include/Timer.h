#pragma once
#include "FileManager.h"

class Level;

class Timer
{
public:

	virtual ~Timer() = default;
	int getTimer()const;
	void setTimer(const int);
	void addTime();
	//	void resetTimer();
	bool ifPastSecond();
	void updateTimer();
	bool ifEndTime()const;
	static Timer& instance(); // return the single timer object
	void draw(sf::RenderWindow& window);
	void getBoardSize(sf::Vector2f size);

private:
	Timer();
	int m_timerInt;
	
	sf::Time m_timer;
	sf::Clock m_clock;
	sf::Text m_timerText; 
	sf::Font m_font;
	sf::Sprite m_clockSprite;
	int m_width;
	int m_height;
	
};