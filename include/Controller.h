#pragma once

#include "Level.h"
#include "PlayerStatus.h"
#include <iostream>
#include <string>
#include <typeinfo>


const int NUM_OF_LEVELS = 3;
const int MENU_NUM = 3;

enum Menu_t{START_GAME , EXIT};

class Controller
{
public:
	Controller();
	void moveDynamic(sf::RenderWindow& window, float timePassed);
	bool checkCollision(DynamicIcon* character, Direction_t direction);
	void run();
	void checkPlayerMovement(float timePassed);
	bool playerEaten(Enemy* enemy);
	void resetDynamics(sf::RenderWindow& window);
	bool levelComplete()const;
	void levelUp(sf::RenderWindow& window);
	bool gameOver()const;
	void setEnd(sf::RenderWindow& window);
	void checkEnemyMovement(Enemy* enemy);
	void startScreen(sf::RenderWindow& window);
	void runMenu();
	void setMenuText();
	void drawMenu(sf::RenderWindow& window);
	Menu_t getMenuButton(sf::Vector2f buttonpos)const;
	void setPlayerNenemies();
	void reset(sf::RenderWindow& window);
	void dig(Direction_t direction);
	bool intoHole(DynamicIcon* character);
	

private:
	PlayerStatus m_statusBar;
	void draw(sf::RenderWindow & window);
	sf::Music m_backroundMusic;
	sf::Music m_menuMusic;
	int m_levelNumber = 1;
	void drawDynamic(sf::RenderWindow & window);
	void setBackground();
	Player m_player;
	vector < std::unique_ptr<Hole>> m_holes;
	vector <std::unique_ptr<Enemy>> m_enemies;
	Level m_level;
	sf::RectangleShape m_screens[NUM_OF_SCREENS];
	sf::Sound m_sound[LEVEL_SOUNDS];
	sf::Font m_fonts[NUM_OF_FONTS];
	sf::Text m_getReady;
	sf::Text m_menutxt[MENU_NUM];
	sf::Text m_finalScore;
	bool m_won = false;
	bool m_timeOver = false;
	bool m_holeMade = false;
	sf::Clock m_holeClock;
	sf::Time m_holeTime;
	int m_holeTimer = 0;

	
};

