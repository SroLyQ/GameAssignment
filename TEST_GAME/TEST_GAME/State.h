#pragma once
#include "Initial.h"
class State
{
public:
	State();

	void setGameState(int gameState);
	void setPauseTime(float pauseTime);
	void setActiveDelayButton(bool active);
	void setShowHighScore(bool active);
	void setShowHowToPlay(bool active);
	void setCloseGame(bool active);
	void setPushButton(bool active);
	void Update();

	float getPauseTime() { return pauseTime; }
	int getGameState() { return gameState; }
	bool isActiveDelayButton() { return activeDelayButton; }
	bool isCloseGame() { return closeGame; }
	bool isShowHighscore() { return activeHighscore; }
	bool isShowHowToPlay() { return activeHowToPlay; }
	bool isPushButton() { return isPushBool; }

private:
	sf::Clock delayButtonPressClock;

	float delayButtonPress;
	int gameState;
	float pauseTime;
	bool activeDelayButton;
	bool activeHighscore;
	bool activeHowToPlay;
	bool closeGame;
	bool isPushBool = false;
};
