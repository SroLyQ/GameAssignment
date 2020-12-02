#pragma once
#include "Initial.h"
class Button
{
public:
	Button(sf::Vector2f position, sf::Vector2f size, sf::Font* font, std::string text, sf::Texture* texture, int state, int type,sf::SoundBuffer* buttonHitBuffer);

	void Update(sf::Vector2i mousePos, State* gameState);
	void Draw(sf::RenderWindow& window);

	int isShowInGameState() { return state; }
	int getType() { return type; }
private:
	sf::RectangleShape body;
	sf::Font* font;
	sf::Text text;

	sf::SoundBuffer buttonHitBuffer;
	sf::Sound buttonHitSF;

	int state;
	int type;
	bool pressed;
};