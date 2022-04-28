#include "Level.h"


Level::Level(int levelNumber)
{
	read_level(levelNumber);
}
//-------------------------------------------------------------
sf::Vector2f Level::getBoardSize()const
{
	sf::Vector2f boardSize;
	boardSize.x = m_board.size() * P_SIZE;
	boardSize.y = m_board[0].size() * P_SIZE;
	return boardSize;
}
//-------------------------------------------------------------
void Level::drawStatic(sf::RenderWindow & window)
{
	for (size_t i = 0; i < m_board.size(); i++)
	{
		for (size_t j = 0; j < m_board[i].size(); j++)
		{
			if (m_board[i][j] != nullptr)
				m_board[i][j]->draw(window,sf::Vector2f(j*P_SIZE,i*P_SIZE));
		}
	}
}
vector<vector<std::unique_ptr<StaticIcon>>>& Level::setBoard()
{
	return m_board;
}
//-------------------------------------------------------------
void Level::open_file(ifstream& input, int levelNumber)
{
	string file = std::to_string(levelNumber) + ".txt";
	input.open(file);
	if (!input.is_open())
	{
		std::cerr << "could not open file\n";
		exit(EXIT_FAILURE);
	}
}
//-------------------------------------------------------------
// this function reads the .txt file and sets the board accordingly
void Level::read_level(int levelNumber)
{
	ifstream input;
	open_file(input,levelNumber);

	int rows, cols , time;
	char c;

	input >> rows >> cols >> time;
	Timer::instance().setTimer(time);
	setBoardSize(rows, cols);

	for (size_t i = 0; i < rows; i++)
	{
		input.get();
		for (size_t j = 0; j < cols; j++)
		{
			c = input.get();
			add_to_board(c, i, j);
		}
	}
}
//-------------------------------------------------------------
StaticIcon * Level::getIcon(sf::Vector2f pos)
{	
	int i = pos.y / P_SIZE;
	int j = pos.x / P_SIZE;
	return m_board[i][j].get();
}
//-------------------------------------------------------------
void Level::add_to_board(const char c,
	const size_t i,
	const size_t j)
{
	switch (c)
	{
	case '#':
		m_board[i][j] = std::make_unique < Wall >(sf::Vector2f(j, i));
		break;
	case '*':
		m_board[i][j] = std::make_unique < Coin >(sf::Vector2f(j, i));
		setCoinCounter(1);
		break;
	case 'H':
		m_board[i][j] = std::make_unique < Ladder >(sf::Vector2f(j, i));
		break;
	case '-':
		m_board[i][j] = std::make_unique < Bar >(sf::Vector2f(j, i));
		break;
	case '?':
		m_board[i][j] = std::make_unique < SpecialObject >(sf::Vector2f(j, i));
		break;
	case '%':
		setEnemyPos(sf::Vector2f((j * P_SIZE) - 16, (i * P_SIZE) + 16));
		break;
	case '@':
		setPlayerPos(sf::Vector2f((j*P_SIZE)- 16, (i*P_SIZE)+16));
		break;
	default:
		break;
	}
}
//-------------------------------------------------------------
// this function sets the board to a new size
void Level::setBoardSize(int rows, int cols)
{
	m_board.resize(rows);
	for (size_t i = 0; i < rows; i++)
		m_board[i].resize(cols);
}
//-------------------------------------------------------------
void Level::setCoinCounter(int x)
{
	m_coinCounter += x;
}
//-------------------------------------------------------------
void Level::resetCoinCounter()
{
	m_coinCounter = 0;
}
//-------------------------------------------------------------
//sets the vector of enemy positions
void Level::setEnemyPos(sf::Vector2f pos)
{
	m_enemyPos.push_back(pos);
}
//-------------------------------------------------------------
void Level::setPlayerPos(sf::Vector2f pos)
{
	m_playerPos = pos;
}
//-------------------------------------------------------------
vector<sf::Vector2f> Level::getEnemyPos() const
{
	return m_enemyPos;
}
//-------------------------------------------------------------
sf::Vector2f Level::getPlayerPos() const
{
	return m_playerPos;
}
//-------------------------------------------------------------
int Level::getCoins() const
{
	return m_coinCounter;
}
//-------------------------------------------------------------
void Level::resetPositions()
{
	m_enemyPos.clear();
}
//-------------------------------------------------------------
//checks if a static object needs to be deleted from the screen
void Level::checkBoard()
{
	sf::Vector2f check(-1, -1);
	int rows = (int)m_board.size();
	int cols = (int)m_board[1].size();
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
		{
			if (m_board[i][j] != nullptr)
			{
				if (m_board[i][j]->getPosition() == check)
				{
					m_board[i][j] = nullptr;
				}
			}
		}

}
//-------------------------------------------------------------



