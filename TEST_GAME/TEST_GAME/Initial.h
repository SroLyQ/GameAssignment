#pragma once
#define MENU 1
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
#include <iostream>
#include <Windows.h>
#include <vector>
#include <string>
#include "State.h"

class Initial
{
public:
	Initial();
	~Initial();

private:
};

