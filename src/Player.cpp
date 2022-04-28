#include "Player.h"

#include "Enemy.h"
#include "Coin.h"
#include "Wall.h"
#include "Level.h"
#include "Bar.h"
#include "SpecialObject.h"
#include "Ladder.h"
#include "Hole.h"


Player::Player()
{
	m_sprite.setTexture(*(FileManager::instance().getIconTexture(PLAYER)));
	m_sprite.setOrigin(16, 16);
	SetPosition(m_sprite.getOrigin());
	m_sound[GOT_COIN].setBuffer(*(FileManager::instance().getGameSound(GOT_COIN)));
	m_sound[DEATH].setBuffer(*(FileManager::instance().getGameSound(DEATH)));
	m_sound[EXTRA_HEALTH].setBuffer(*(FileManager::instance().getGameSound(EXTRA_HEALTH)));
	m_sound[MORE_TIME].setBuffer(*(FileManager::instance().getGameSound(MORE_TIME)));
	m_sound[EXTRA_ENEMY].setBuffer(*(FileManager::instance().getGameSound(EXTRA_ENEMY)));
	m_sound[DIG].setBuffer(*(FileManager::instance().getGameSound(DIG)));
}
//-------------------------------------------------------------
void Player::SetPosition(sf::Vector2f new_pos)
{
	m_sprite.setPosition(new_pos);
}
//-------------------------------------------------------------
void Player::setDirection(Direction_t direction)
{
	m_newDirection = direction;
}
//-------------------------------------------------------------
void Player::move(float timePassed, sf::Vector2f boardSize)
{
	m_prevPos = m_sprite.getPosition();
	m_direction = m_newDirection;
	float distance = m_speed * timePassed;

	switch (m_direction)
	{
	case UP:
		m_sprite.move(0, -distance);
		break;
	case DOWN:
		m_sprite.move(0, distance);
		break;
	case RIGHT:
		m_sprite.move(distance, 0);
		break;
	case LEFT:
		m_sprite.move(-distance, 0);
		break;
	}

	if (outOfBoard(boardSize))
		m_sprite.setPosition(m_prevPos);
	m_pos = m_sprite.getPosition();
}
//-------------------------------------------------------------
void Player::draw(sf::RenderWindow & window)
{
	window.draw(m_sprite);	
}
//-------------------------------------------------------------
Direction_t Player::getDirection()const
{
	return m_direction;
}
//-------------------------------------------------------------
void Player::collide(Enemy* object)
{
	m_life--;
	m_sound[DEATH].play();
	m_eaten = true;
}
//-------------------------------------------------------------
void Player::collide(SpecialObject* object)
{

	Special_t special = object->getSpecial();//gets the special object type

	
	switch(special)
	{
	case LIFE:
		setLife(1);
		m_sound[EXTRA_HEALTH].play();
		break;
	case SCORE:
		m_sound[GOT_COIN].play();
		setScore(10);
		break;
	case TIME:
		m_sound[MORE_TIME].play();
		Timer::instance().addTime();
		break;
	case ADD_ENEMY:
		setAddEnemy();
		m_sound[EXTRA_ENEMY].play();
		break;
	}
	object->collide(this);
}
//-------------------------------------------------------------
void Player::collide(Coin* object)
{
	setAteCoin();
	m_sound[GOT_COIN].play();
	object->collide(this);
}
//-------------------------------------------------------------
void Player::collide(Wall* object)
{
	m_sprite.setPosition(m_prevPos);
}
//-------------------------------------------------------------
void Player::collide(Ladder* object)
{
	m_onLadder = true;
}
//-------------------------------------------------------------
void Player::collide(Hole* object)
{
	m_sound[DIG].play();
	sf::Vector2f pos(object->getPosition().x + P_SIZE/2, m_pos.y + (P_SIZE-5.f));
	SetPosition(pos);
	m_inHole = true;
}
//-------------------------------------------------------------
void Player::collide(Bar* object)
{
	sf::Vector2f align(getPosition().x, getPosition().y + (P_SIZE / 2));
	SetPosition(align);
	m_onRope = true;
}
//-------------------------------------------------------------
int Player::getLife()const
{
	return m_life;
}
//-------------------------------------------------------------
int Player::getScore() const
{
	return m_score;
}
//-------------------------------------------------------------
void Player::setLife(int x)
{
	m_life += x;
	if (m_life > 3)
		m_life = 3;
}
//-------------------------------------------------------------
// this function sets the player's score
void Player::setScore(int x)
{
	m_score += x;
}
//-------------------------------------------------------------
bool Player::isEaten()const
{
	return m_eaten;
}
//-------------------------------------------------------------
void Player::setEaten()
{
	m_eaten = false;
}
//-------------------------------------------------------------
bool Player::onRope()const
{
	return m_onRope;
}
//-------------------------------------------------------------
void Player::setOnRope()
{
	if (m_onRope)
		m_onRope = false;
	else
		m_onRope = true;
}
//-------------------------------------------------------------
void Player::resetScore()
{
	m_score = 0;
}
//-------------------------------------------------------------
void Player::setAddEnemy()
{
	if (m_addEnemy)
		m_addEnemy = false;
	else
		m_addEnemy = true;

}
//-------------------------------------------------------------
bool Player::addEnemy()
{
	return m_addEnemy;
}
//-------------------------------------------------------------
bool Player::ateCoin() const
{
	return m_ateCoin;
}
//-------------------------------------------------------------
void Player::setAteCoin()
{
	if (m_ateCoin)
		m_ateCoin = false;
	else
		m_ateCoin = true;
}
//-------------------------------------------------------------
bool Player::inHole() const
{
	return m_inHole;
}
//-------------------------------------------------------------
void Player::setInHole()
{
	m_inHole = false;
}
//-------------------------------------------------------------






