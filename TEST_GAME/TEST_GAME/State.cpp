#include "State.h"

State::State()
{
	this->delayButtonPress = 0.0f;
	this->activeDelayButton = false;
	this->gameState = MENU;
	this->activeHighscore = false;
	this->activeHowToPlay = false;
	this->pauseTime = 0.0f;
	this->closeGame = false;
}

void State::setGameState(int gameState)
{
	this->gameState = gameState;
}

void State::setPauseTime(float pauseTime)
{
	this->pauseTime = pauseTime;
}

void State::setActiveDelayButton(bool activeDelayButton)
{
	this->activeDelayButton = activeDelayButton;
}

void State::setShowHighScore(bool active)
{
	this->activeHighscore = active;
}

void State::setShowHowToPlay(bool active)
{
	this->activeHowToPlay = active;
}

void State::setCloseGame(bool active)
{
	this->closeGame = active;
}

void State::setPushButton(bool active)
{
	this->isPushBool = active;
}

void State::Update()
{
	if (activeDelayButton) {
		delayButtonPress = delayButtonPressClock.getElapsedTime().asSeconds();
		if (delayButtonPress > 0.2f) {
			activeDelayButton = false;
			delayButtonPress = 0.0f;
			delayButtonPressClock.restart();
		}
	}
	else {
		delayButtonPressClock.restart();
	}
}