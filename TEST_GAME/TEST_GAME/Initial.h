#pragma once
#define MENU 1
#define MENU_START 11
#define MENU_HIGHSCORE 12
#define MENU_HIGHSCORE_EXIT 121
#define MENU_EXIT 13
#define GAME 2
#define END_GAME 3
#define END_GAME_CONTINUE 31
#define PAUSE 4
#define PAUSE_RUsure 41
#define RESUME 5
#define EXIT 6
#define EXIT_YES 61
#define EXIT_NO 62
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <Windows.h>
#include <vector>
#include <string>
#include "State.h"
#include <sstream>

class Initial
{
public:
	Initial();
	~Initial();

private:
};

