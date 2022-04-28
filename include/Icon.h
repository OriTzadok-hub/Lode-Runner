#pragma once

#include <SFML\Audio.hpp>
#include <SFML\Graphics.hpp>
#include "FileManager.h"
#include <vector>

using std::vector;

class Player;
class Wall;
class Enemy;
class Hole;
class Coin;
class Bar;
class Level;
class Ladder;
class SpecialObject;
class RandomEnemy;
class SmartEnemy;
class StaticEnemy;

enum Object_t { PLAYER, ENEMY,COIN, WALL ,LADDER ,BAR,SPECIAL,HOLE};
enum levelSound_t { LEVEL_UP, GAME_OVER,WIN , CLICK};
enum gameSound_t { GOT_COIN , DEATH , EXTRA_HEALTH , MORE_TIME , EXTRA_ENEMY ,DIG};
const int P_SIZE = 32; //cell size
class Icon
{
public:
	Icon() {};
	~Icon() {};

	virtual void collide(Icon* object) = 0;
	virtual void collide(Player* object) = 0;
	virtual void collide(Enemy* object) = 0;
	virtual void collide(Ladder* object) = 0;
	virtual void collide(Coin* object) = 0;
	virtual void collide(Wall* object) = 0;
	virtual void collide(Bar* object) = 0;
	virtual void collide(SpecialObject* object) = 0;
	virtual void collide(Hole* object) =0;
	
	


protected:
	Object_t m_type;
	sf::Vector2f m_pos;
	sf::Sprite m_sprite;

};

