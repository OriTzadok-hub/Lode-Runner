#pragma once

#include "Icon.h"
#include <fstream>
#include <memory>
#include <string>
#include <iostream>
#include <vector>

using std::ifstream;
using std::string;


const int NUM_OF_ICONS = 8;
const int LEVEL_SOUNDS = 4;
const int GAME_SOUNDS = 6;
const int NUM_OF_SCREENS = 4;
const int NUM_OF_FONTS = 3;

enum Screen_t{BACKGROUND,START,YOUWIN,GAMEOVER};

enum Fonts_t{TITLE,MENU_TXT,INGAME};


class FileManager
{
public:
	sf::Texture * getIconTexture(size_t shape) ;
	sf::Texture* getScreenTexture(size_t shape);
	sf::SoundBuffer* getLevelSound(size_t type);
	sf::SoundBuffer* getGameSound(size_t type);
	sf::Texture* getLifeTexture();
	sf::Texture* getClockTexture();
	sf::Font* getFont(size_t type);
	static FileManager & instance();


private:
	FileManager();
	sf::Texture m_pTexture[NUM_OF_ICONS];
	sf::Font m_fonts[NUM_OF_FONTS];
	sf::Texture m_life;
	sf::Texture m_clock;
	sf::SoundBuffer m_levelSounds[LEVEL_SOUNDS];
	sf::SoundBuffer m_gameSounds[GAME_SOUNDS];
	sf::Texture m_screens[NUM_OF_SCREENS];

};

