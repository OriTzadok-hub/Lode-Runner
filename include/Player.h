#pragma once
#include "DynamicIcon.h"


class Player : public DynamicIcon
{
public:
	Player();

	void SetPosition(sf::Vector2f new_pos);
	void setDirection(Direction_t direction);
	void move(float timePassed, sf::Vector2f boardSize);
	void draw(sf::RenderWindow &window);
	Direction_t getDirection()const;

	virtual void collide(Icon* object) {};
	virtual void collide(Player* object) {};
	virtual void collide(Enemy* object);
	virtual void collide(Coin* object);
	virtual void collide(Wall* object);
	virtual void collide(Bar* object);
	virtual void collide(SpecialObject* object) ;
	virtual void collide(Ladder* object) ;
	virtual void collide(Hole* object) ;
	
	
	int getLife()const;
	int getScore() const;
	void setLife(int x);
	void setScore(int x);
	bool isEaten()const;
	void setEaten();
	bool onRope()const;
	void setOnRope();
	bool onLadder()const;
	void setOnLadder();
	void resetScore();
	void setAddEnemy();
	bool addEnemy();
	bool ateCoin()const;
	void setAteCoin();
	bool inHole()const;
	void setInHole();


private:

	int m_score = 0;
	int m_life = 3;
	Direction_t m_newDirection;
	float m_speed = 40;
	bool m_eaten = false;
	bool m_onRope = false;
	bool m_onLadder = false;
	sf::Sound m_sound[GAME_SOUNDS];
	bool m_addEnemy = false;
	bool m_ateCoin= false;
	bool m_inHole = false;
};


