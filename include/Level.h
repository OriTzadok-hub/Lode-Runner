#pragma once
#include "Player.h"
#include "Enemy.h"
#include "Coin.h"
#include "Wall.h"
#include "Ladder.h"
#include "Hole.h"
#include "Bar.h"
#include "Timer.h"
#include "SpecialObject.h"
#include "FileManager.h"
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include "SmartEnemy.h"
#include "RandomEnemy.h"
#include "StaticEnemy.h"

using std::ifstream;
using std::string;

class Level
{
public:
	Level( int levelNumber);

	sf::Vector2f getBoardSize()const;
	void read_level( int levelNumber);
	StaticIcon * getIcon(sf::Vector2f pos);
	void drawStatic(sf::RenderWindow & window);
	vector<vector<std::unique_ptr<StaticIcon>>>& setBoard();
	
	void setCoinCounter(int x);
	int getCoins() const;
	void resetCoinCounter();
	void setEnemyPos(sf::Vector2f pos);
	void setPlayerPos(sf::Vector2f pos);
	vector<sf::Vector2f> getEnemyPos()const;
	sf::Vector2f getPlayerPos()const;
	void resetPositions();
	void checkBoard();
private:
	void open_file(ifstream& input, int levelNumber);
	void add_to_board(char c,size_t i, size_t j);
	void setBoardSize(int rows, int cols);
	vector <vector<std::unique_ptr<StaticIcon>>> m_board;
	int m_coinCounter = 0;
	vector <sf::Vector2f> m_enemyPos;
	sf::Vector2f m_playerPos;


};


