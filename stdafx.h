#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include <string>
#include <random>
#include <chrono>
#include <vector>
#include <memory>
#include <cassert>
#include <sstream>
#include <fstream>
#include <iterator>
#include <iostream>
#include <algorithm>
#include <exception>
#include <functional>
#include <unordered_map>


#define OK_BUTTON "OK"
#define GAME_TEXT "GAME"
#define QUIT_BUTTON "Quit"
#define PLAY_BUTTON "Play"
#define TITLE_TEXT "Memory"
#define PLAYER_TEXT "Player: "
#define REPEAT_BUTTON "Try again"
#define END_TEXT "CONGRATULATIONS"


template <typename T>
using sPtr = std::shared_ptr<T>;


inline double PI()
{
	return std::acos(-1);
}


namespace Main
{
	extern sf::RenderWindow window;

	extern unsigned int screenWidth;
	extern unsigned int screenHeight;

	extern float cardWidht;
	extern float cardHeight;
}


namespace Filename
{
	// Fonts:
	extern const std::string font1;
	extern const std::string font2;

	// Textures:
	extern const std::string menu;
	extern const std::string paper;
	extern const std::string sound;
	extern const std::string noSound;
	extern const std::string backCard;
	extern const std::string background;

	// Audio:
	extern const std::string cardFlip;
	extern const std::string matchCards;
	extern const std::string clickSound;
	extern const std::string musicFilename;
}


