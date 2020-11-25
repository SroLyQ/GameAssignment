#pragma once
#include "Initial.h"
class Button
{
	public:
		Button(sf::Vector2f position , sf::Vector2f size, sf::Font* font, std::string text, sf::Texture* texture, int state, int type);
		
		void Update(sf::Vector2i mousePos, State* gameState);
		void Draw(sf::RenderWindow& window);

		int isShowInGameState() { return state; }
	private:
		sf::RectangleShape body;
		sf::Font* font;
		sf::Text text;

		int state;
		int type;
		bool pressed;
};

