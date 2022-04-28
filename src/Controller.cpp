
#include "Controller.h"



Controller::Controller() : m_player(), m_enemies(), m_level(m_levelNumber)
{
	m_sound[LEVEL_UP].setBuffer(*(FileManager::instance().getLevelSound(LEVEL_UP)));
	m_sound[GAME_OVER].setBuffer(*(FileManager::instance().getLevelSound(GAME_OVER)));
	m_sound[WIN].setBuffer(*(FileManager::instance().getLevelSound(WIN)));
	m_sound[CLICK].setBuffer(*(FileManager::instance().getLevelSound(CLICK)));
	m_backroundMusic.openFromFile("perion.wav");
	m_backroundMusic.setVolume(50);
	m_backroundMusic.setLoop(true);
	m_menuMusic.openFromFile("menumusic.wav");
	m_menuMusic.setVolume(50);
	m_menuMusic.setLoop(true);
	m_screens[BACKGROUND].setTexture((FileManager::instance().getScreenTexture(BACKGROUND)));
	m_screens[GAMEOVER].setTexture((FileManager::instance().getScreenTexture(GAMEOVER)));
	m_screens[START].setTexture((FileManager::instance().getScreenTexture(START)));
	m_screens[YOUWIN].setTexture((FileManager::instance().getScreenTexture(YOUWIN)));
	m_fonts[INGAME] = (*(FileManager::instance().getFont(INGAME)));
	m_fonts[TITLE] = (*(FileManager::instance().getFont(TITLE)));
	m_fonts[MENU_TXT] = (*(FileManager::instance().getFont(MENU_TXT)));
	m_getReady.setFont(m_fonts[INGAME]);
	m_menutxt[TITLE].setFont(m_fonts[TITLE]);
	m_menutxt[MENU_TXT].setFont(m_fonts[MENU_TXT]);
	m_menutxt[MENU_TXT+1].setFont(m_fonts[MENU_TXT]);
	m_finalScore.setFont(m_fonts[INGAME]);
	
}
//-------------------------------------------------------------
void Controller::run()
{
	m_won = false;
	m_backroundMusic.play();
	sf::RenderWindow window;
	window.create(sf::VideoMode(m_level.getBoardSize().y, m_level.getBoardSize().x + 50), "Lode Runner");
	startScreen(window);
	reset(window);
	setBackground();
	Timer::instance().getBoardSize(m_level.getBoardSize());
	static sf::Clock clock;
	while (window.isOpen())
	{
		while (!gameOver())
		{
			if (levelComplete())
			{
				m_player.setScore(m_levelNumber * 50);
				m_levelNumber++;
				if (m_levelNumber <= NUM_OF_LEVELS)
					levelUp(window);
				else
				{
					m_won = true;
					break;
				}
			}
			if (Timer::instance().ifEndTime())//if time of level is over
			{
				m_timeOver = true;
				m_player.setLife(-1);
				reset(window);
				m_timeOver = false;
			}
			auto event = sf::Event{};
			if (window.pollEvent(event))
			{
				switch (event.type)
				{
				case sf::Event::Closed:
					m_backroundMusic.stop();
					window.close();
					runMenu();
					break;
				}
			}
			float deltaTime = clock.restart().asSeconds();
			moveDynamic(window, deltaTime);
			Timer::instance().updateTimer();
			draw(window);
			window.display();
			window.clear();
		}
		setEnd(window);
		m_backroundMusic.stop();
		window.close();
		runMenu();
	}
}
//-------------------------------------------------------------
//this function resets the game when new game starts or when time is over
void Controller::reset(sf::RenderWindow& window)
{
	size_t size = m_enemies.size();
	for (size_t i = 0; i < size; i++)
		m_enemies.pop_back();
	m_level.setBoard().clear();
	m_level.resetPositions();
	if (!(m_timeOver))
	{
		m_player.resetScore();
		m_player.setLife(3);
		m_levelNumber = 1;
	}
	m_level.resetCoinCounter();
	m_level.read_level(m_levelNumber);
	setPlayerNenemies();
	setBackground();
	window.create(sf::VideoMode(m_level.getBoardSize().y, m_level.getBoardSize().x + 50), " Lode Runner ");

}
//-------------------------------------------------------------
//sets the player and enemies with their information from the class Level
void Controller::setPlayerNenemies()
{
	vector<sf::Vector2f> positions = m_level.getEnemyPos();
	int size = (int)positions.size();
	for(int i = 0; i < size; i++)
	{
		if (m_enemies.size() % 3 == 0)
			m_enemies.push_back(std::make_unique < SmartEnemy >());
		else if (m_enemies.size() % 3 == 1)
			m_enemies.push_back(std::make_unique < RandomEnemy >());
		else
			m_enemies.push_back(std::make_unique < StaticEnemy >());

		m_enemies[i]->SetPosition(positions[i]);
		m_enemies[i]->setStartingPosition(positions[i]);
	}
	
	m_player.setStartingPosition(m_level.getPlayerPos());
	m_player.SetPosition(m_level.getPlayerPos());
}
//-------------------------------------------------------------
void Controller::draw(sf::RenderWindow & window)
{
	window.draw(m_screens[BACKGROUND]);
	m_level.drawStatic(window);
	m_statusBar.draw(window, m_player.getLife(), m_player.getScore(), m_levelNumber, m_level.getBoardSize());
	Timer::instance().draw(window);
	drawDynamic(window);
	for (size_t i = 0; i < m_holes.size(); i++)
	{
		m_holes[i]->draw(window);
	}
}
//-------------------------------------------------------------
void Controller::drawDynamic(sf::RenderWindow & window)
{
	m_player.draw(window);
	for (size_t i = 0; i < m_enemies.size(); i++)
		m_enemies[i]->draw(window);
}
//-------------------------------------------------------------
void Controller::setBackground()
{
	sf::Vector2f backgroundsize(m_level.getBoardSize().y, m_level.getBoardSize().x + 50);
	m_screens[BACKGROUND].setSize(backgroundsize);
}
//-------------------------------------------------------------
void Controller::moveDynamic(sf::RenderWindow& window, float timePassed)
{
	if (m_player.isEaten())
	{
		resetDynamics(window);//reset dynamic objects locations
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)&&!(m_player.inHole()))
	{
		m_player.setDirection(UP);
		m_player.move(timePassed , m_level.getBoardSize());
		checkCollision(&m_player, m_player.getDirection());
		checkPlayerMovement(timePassed);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !(m_player.inHole()))
	{
		m_player.setDirection(DOWN);
		m_player.move(timePassed, m_level.getBoardSize());
		checkCollision(&m_player, m_player.getDirection());
		checkPlayerMovement(timePassed);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !(m_player.inHole()))
	{
		m_player.setDirection(RIGHT);
		m_player.move(timePassed, m_level.getBoardSize());
		checkCollision(&m_player, m_player.getDirection());
		checkPlayerMovement(timePassed);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !(m_player.inHole()))
	{
		m_player.setDirection(LEFT);
		m_player.move(timePassed, m_level.getBoardSize());
		checkCollision(&m_player, m_player.getDirection());
		checkPlayerMovement(timePassed);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)&&!(m_holeMade))
	{
		dig(LEFT);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::X) && !(m_holeMade))
	{
		dig(RIGHT);
	}
	if (m_holeMade)
	{
		m_holeTime = m_holeClock.getElapsedTime();
		if (m_holeTime.asSeconds() > 1)
		{
			m_holeTimer++;
			m_holeClock.restart();
		}
		if (m_holeTimer == 5)
		{
			if (m_player.inHole())
			{
				sf::Vector2f pos(m_player.getPosition().x - P_SIZE / 2,
									m_player.getPosition().y - (P_SIZE - 5.f));
				m_player.SetPosition(pos);
				m_player.setInHole();
			}
			m_holes.pop_back();
			m_holeMade = false;
			m_holeTimer = 0;
		}

	}
	if (m_player.addEnemy())//if special object result was to add an enemy
	{
		sf::Vector2f newEnemy(m_player.getPosition().x + P_SIZE, m_player.getPosition().y + 1.f);
		m_enemies.push_back(std::make_unique < StaticEnemy >());
		m_enemies[(int)m_enemies.size() - 1]->SetPosition(newEnemy);
		m_player.setAddEnemy();
	}
	if (m_player.ateCoin())
	{
		m_player.setScore(2 * m_levelNumber);
		m_level.setCoinCounter(-1);
		m_player.setAteCoin();
	}
	m_level.checkBoard();//check if static icon needs to be deleted
	for (size_t i = 0; i < m_enemies.size(); i++)
	{
		m_enemies[i]->move(timePassed, m_level.getBoardSize());
		checkCollision(m_enemies[i].get(), m_enemies[i].get()->getDirection());
		if (playerEaten(m_enemies[i].get()))
			m_player.collide(m_enemies[i].get());
		checkEnemyMovement(m_enemies[i].get());
	}
	
}
//-------------------------------------------------------------
void Controller::dig(Direction_t direction)
{
	
	sf::Vector2f prev(m_player.getPosition());
	sf::Vector2f newpos;
	if (direction == LEFT)
	{
		sf::Vector2f left(m_player.getPosition().x - (P_SIZE+10.f), m_player.getPosition().y);
		newpos = left;
	}
	else
	{ 
		sf::Vector2f right(m_player.getPosition().x + (P_SIZE-10.f), m_player.getPosition().y);
		newpos = right;
	}
	m_player.SetPosition(newpos);
	sf::Vector2f down(newpos.x, newpos.y + P_SIZE);
	if(m_level.getIcon(down) != nullptr)
		if (typeid(*m_level.getIcon(down)) == typeid(Wall))		
		{
			m_holes.push_back(std::make_unique < Hole >(m_player.getPosition()));
			m_holeMade = true;
			m_holeClock.restart();
		}

	m_player.SetPosition(prev);
}
//-------------------------------------------------------------
bool Controller::checkCollision(DynamicIcon* character, Direction_t direction)
{
	Icon* icon = m_level.getIcon(character->getNextDirection(direction));
	if (icon != nullptr)
	{
		icon->collide(character);
		return true;
	}
	else if (m_holeMade)
	{
		if (intoHole(character))
			m_holes[0].get()->collide(character);
	}
	return false;
}
//-------------------------------------------------------------
void Controller::checkPlayerMovement(float timePassed)
{
	
	if (m_player.onRope())
	{
		sf::Vector2f fixpos(m_player.getPosition().x, m_player.getPosition().y - (P_SIZE / 2));
		m_player.SetPosition(fixpos);
		m_player.setOnRope();
	}
	sf::Vector2f below(m_player.getNextDirection(DOWN));
	if (m_level.getIcon(below) == nullptr)//if needs to fall
	{
		bool fall = true;
		while (fall)
		{
			m_player.setDirection(DOWN);
			m_player.move(timePassed, m_level.getBoardSize());
			if (checkCollision(&m_player, m_player.getDirection()))
					fall = false;
		}
	}
}
//-------------------------------------------------------------
void Controller::checkEnemyMovement(Enemy* enemy)
{
	sf::Vector2f below(enemy->getNextDirection(DOWN));
	if (m_level.getIcon(below) == nullptr||(typeid(*m_level.getIcon(below)) == typeid(Bar)))
	{
		enemy->SetPosition(enemy->getPrevPos());
		enemy->setStuck();
	}
}
//-------------------------------------------------------------
bool Controller::playerEaten(Enemy* enemy)
{
	return (abs(m_player.getPosition().x - enemy->getPosition().x) < (P_SIZE/2) &&
		abs(m_player.getPosition().y - enemy->getPosition().y) < (P_SIZE/2));
}
//-------------------------------------------------------------
bool Controller::intoHole(DynamicIcon* character)
{
	if (abs(m_holes[0].get()->getPosition().x - character->getPosition().x) < (P_SIZE/2)&&
		abs(m_holes[0].get()->getPosition().y - character->getPosition().y) < (P_SIZE / 2))
		return true;
	else
		return false;
}
//-------------------------------------------------------------
void Controller::resetDynamics(sf::RenderWindow& window)
{
	m_player.SetPosition(m_player.getStartingPosition());
	for (size_t i = 0; i < m_enemies.size(); i++)
		m_enemies[i]->SetPosition(m_enemies[i]->getStartingPosition());
	m_player.setEaten();
	
}
//-------------------------------------------------------------
bool Controller::levelComplete()const
{
	return m_level.getCoins() == 0;
}
//-------------------------------------------------------------
//updates screen and objects to next level
void Controller::levelUp(sf::RenderWindow& window)
{
	m_sound[LEVEL_UP].play();
	size_t size = m_enemies.size();
	for (size_t i = 0; i < size; i++)
		m_enemies.pop_back();
	m_level.setBoard().clear();
	m_level.resetPositions();
	m_level.read_level(m_levelNumber);
	setPlayerNenemies();
	setBackground();
	window.create(sf::VideoMode(m_level.getBoardSize().y, m_level.getBoardSize().x + 50), " Lode Runner ");

}
//-------------------------------------------------------------
bool Controller::gameOver()const
{
	if (m_player.getLife() <= 0)
	{
		
		return true;
	}
	else
		return false;
}
//-------------------------------------------------------------
//sets the ending screen of loss or win.
void Controller::setEnd(sf::RenderWindow& window)
{

	sf::Clock clock;
	sf::Time timePassed;
	sf::Vector2f backgroundsize(m_level.getBoardSize().y, m_level.getBoardSize().x + 50);
	if(m_won)
	{
		m_screens[YOUWIN].setSize(backgroundsize);
		std::string score = "YOUR SCORE : " + std::to_string(m_player.getScore());
		m_finalScore.setPosition(m_level.getBoardSize().y / 2 - 70, m_level.getBoardSize().x - 50);
		m_finalScore.setString(score);
	}
	else
		m_screens[GAMEOVER].setSize(backgroundsize);
	clock.restart();
	timePassed = clock.getElapsedTime();
	m_sound[WIN].play();
	while (timePassed.asSeconds() < 7)
	{
		window.clear();
		if (m_won)
		{
			window.draw(m_screens[YOUWIN]);
			window.draw(m_finalScore);
		}
		else
			window.draw(m_screens[GAMEOVER]);
		window.display();
		timePassed = clock.getElapsedTime();
	}

}
//-------------------------------------------------------------
//sets the get ready screen
void Controller::startScreen(sf::RenderWindow& window)
{
	std::string getReady;
	sf::Clock clock;
	sf::Time timePassed;
	sf::Vector2f backgroundsize(m_level.getBoardSize().y, m_level.getBoardSize().x + 50);
	m_screens[START].setSize(backgroundsize);
	m_getReady.setCharacterSize(P_SIZE);
	m_getReady.setOutlineColor(sf::Color::Black);
	m_getReady.setOutlineThickness(3);
	clock.restart();
	
	for (int i = 0;i < 6;)
	{
		getReady = "GET READY!  " + std::to_string(5 - i);
		m_getReady.setPosition(m_level.getBoardSize().y / 2 - 70, m_level.getBoardSize().x / 2);
		m_getReady.setString(getReady);
		timePassed = clock.getElapsedTime();
		window.draw(m_screens[START]);
		window.draw(m_getReady);
		if (timePassed.asSeconds() > 1)
		{
			i++;
			clock.restart();
		}
		window.display();
		window.clear();
	}
}
//-------------------------------------------------------------
void Controller::runMenu()
{
	sf::RenderWindow window;
	window.create(sf::VideoMode(600, 600), "Lode Runner");
	sf::Vector2f size(600,600);
	m_screens[START].setSize(size);
	setMenuText();
	m_menuMusic.play();
	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::MouseButtonReleased:
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					Menu_t button = getMenuButton(sf::Vector2f(event.mouseButton.x, event.mouseButton.y));
					switch (button)
					{
					case START_GAME: 
						m_menuMusic.stop();
						m_sound[CLICK].play();
						window.close();
						run();
						break;
					case EXIT:
						m_sound[CLICK].play();
						window.close();   
						break;
					default:
						break;
					}
				}
				break;
			}
		}
		drawMenu(window);
		window.display();
		window.clear();
	}
}
//-------------------------------------------------------------
//sets the menu's text objects
void Controller::setMenuText()
{
	std::string title = "LODE RUNNER";
	m_menutxt[TITLE].setPosition(172, 70);
	m_menutxt[TITLE].setString(title);
	m_menutxt[TITLE].setScale(1.2, 1.2);
	m_menutxt[TITLE].setColor(sf::Color::Black);
	std::string start = "NEW GAME";
	m_menutxt[MENU_TXT].setPosition(202, 250);
	m_menutxt[MENU_TXT].setCharacterSize(P_SIZE * 2);
	m_menutxt[MENU_TXT].setString(start);
	m_menutxt[MENU_TXT].setColor(sf::Color::Black);
	std::string exit = "EXIT";
	m_menutxt[MENU_TXT+1].setPosition(255, 350);
	m_menutxt[MENU_TXT + 1].setCharacterSize(P_SIZE*2);
	m_menutxt[MENU_TXT + 1].setString(exit);
	m_menutxt[MENU_TXT + 1].setColor(sf::Color::Black);
}
//-------------------------------------------------------------
void Controller::drawMenu(sf::RenderWindow& window)
{
	window.draw(m_screens[START]);
	window.draw(m_menutxt[TITLE]);
	window.draw(m_menutxt[MENU_TXT]);
	window.draw(m_menutxt[MENU_TXT + 1]);
}
//-------------------------------------------------------------
Menu_t Controller::getMenuButton(sf::Vector2f buttonpos)const
{
	if (m_menutxt[MENU_TXT].getGlobalBounds().contains(buttonpos))
	{
		
		return START_GAME;
	}
	else if (m_menutxt[MENU_TXT+1].getGlobalBounds().contains(buttonpos))
	{
		return EXIT;
	}
}
//-------------------------------------------------------------

