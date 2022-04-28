#include "FileManager.h"

//loads all textures , fonts and sound buffers.
FileManager::FileManager()
{
	
	m_pTexture[PLAYER].loadFromFile("player.png");
	m_pTexture[ENEMY].loadFromFile("enemy.png");
	m_pTexture[COIN].loadFromFile("coin.png");
	m_pTexture[WALL].loadFromFile("wall.png");
	m_pTexture[LADDER].loadFromFile("ladder (2).png");
	m_pTexture[BAR].loadFromFile("bar.png");
	m_pTexture[SPECIAL].loadFromFile("special.png");
	m_pTexture[HOLE].loadFromFile("hole.png");
	

	m_life.loadFromFile("heart.png");
	m_clock.loadFromFile("alarm-clock.png");

	m_fonts[TITLE].loadFromFile("title.ttf");
	m_fonts[MENU_TXT].loadFromFile("menu.ttf");
	m_fonts[INGAME].loadFromFile("gameFont.otf");

	m_gameSounds[GOT_COIN].loadFromFile("got_coin.wav");
	m_gameSounds[EXTRA_ENEMY].loadFromFile("extra_enemy.wav");
	m_gameSounds[MORE_TIME].loadFromFile("extratime.wav");
	m_gameSounds[DEATH].loadFromFile("death.wav");
	m_gameSounds[EXTRA_HEALTH].loadFromFile("healthup.wav");
	m_gameSounds[DIG].loadFromFile("dig.wav");

	m_levelSounds[LEVEL_UP].loadFromFile("lvlup.wav");
	m_levelSounds[GAME_OVER].loadFromFile("gameover.wav");
	m_levelSounds[WIN].loadFromFile("win.wav");
	m_levelSounds[CLICK].loadFromFile("click.wav");

	m_screens[BACKGROUND].loadFromFile("background.jpg");
	m_screens[START].loadFromFile("start.png");
	m_screens[YOUWIN].loadFromFile("winscreen.jpg");
	m_screens[GAMEOVER].loadFromFile("gameoverscreen.jpg");
}
//-------------------------------------------------------------
sf::Texture * FileManager::getIconTexture(size_t shape)
{
	return & m_pTexture[shape];
}
//-------------------------------------------------------------
sf::Texture* FileManager::getScreenTexture(size_t shape)
{
	return &m_screens[shape];
}
//-------------------------------------------------------------
sf::SoundBuffer* FileManager::getLevelSound(size_t type)
{
	return &m_levelSounds[type];
}
//-------------------------------------------------------------
sf::SoundBuffer* FileManager::getGameSound(size_t type)
{
	return &m_gameSounds[type];
}
//-------------------------------------------------------------
sf::Texture* FileManager::getLifeTexture()
{
	return &m_life;
}
//-------------------------------------------------------------
sf::Texture* FileManager::getClockTexture()
{
	return &m_clock;
}
//-------------------------------------------------------------
sf::Font* FileManager::getFont(size_t type)
{
	return &m_fonts[type];
}
//-------------------------------------------------------------
FileManager & FileManager::instance()
{
	static FileManager instance;
	return instance;
}
//-------------------------------------------------------------


