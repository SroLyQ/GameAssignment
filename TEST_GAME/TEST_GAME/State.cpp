#include "State.h"

State::State()
{
	this->delayButtonPress = 0.0f;
	this->activeDelayButton = false;
	this->gameState = GAME;
	this->pauseTime = 0.0f;
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
