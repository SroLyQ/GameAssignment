#pragma once
#include "Initial.h"
class Button
{
	public:
		Button(sf::Vector2f position , sf::Vector2f size, sf::Font* font, std::string text, sf::Texture* texture);

		void Draw(sf::RenderWindow& window);
	private:
		sf::RectangleShape body;
		sf::Font* font;
		sf::Text text;
};

