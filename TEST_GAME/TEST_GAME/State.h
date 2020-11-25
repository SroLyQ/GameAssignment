#pragma once
#include "Initial.h"
class State
{
	public:
		State();

		void setGameState(int gameState);
		void setPauseTime(float pauseTime);
		void setActiveDelayButton(bool active);
		void Update();

		float getPauseTime() { return pauseTime; }
		int getGameState() { return gameState; }
		bool isActiveDelayButton() { return activeDelayButton; }

	private:
		sf::Clock delayButtonPressClock;

		float delayButtonPress;
		int gameState;
		float pauseTime;
		bool activeDelayButton;
};

