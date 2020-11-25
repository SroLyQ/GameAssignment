#include "Button.h"

Button::Button(sf::Vector2f position, sf::Vector2f size, sf::Font* font, std::string text, sf::Texture* texture,int state, int type)
{
	body.setSize(size);
	body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(position);
	body.setTexture(texture);
	this->state = state;
	this->type = type;
	this->font = font;
	this->text.setFont(*this->font);
	switch (type) {
		case RESUME:
			this->text.setPosition(sf::Vector2f(position.x - 70.0f, position.y - 11.0f));
			this->text.setFillColor(sf::Color::Green);
			this->text.setCharacterSize(24);
			break;
		case EXIT:
			this->text.setPosition(sf::Vector2f(position.x - 48.0f, position.y - 11.0f));
			this->text.setFillColor(sf::Color::Red);
			this->text.setCharacterSize(24);
			break;
		case END_GAME_CONTINUE:
			this->text.setPosition(sf::Vector2f(position.x - 80.0f, position.y - 11.0f));
			this->text.setFillColor(sf::Color::White);
			this->text.setCharacterSize(20);
			break;
	}
	this->text.setOutlineColor(sf::Color::Black);
	this->text.setOutlineThickness(2);
	this->text.setString(text);
}

void Button::Update(sf::Vector2i mousePos,State* gameState)
{
	if (this->body.getGlobalBounds().contains(sf::Vector2f(mousePos)) ) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !gameState->isActiveDelayButton()) {
			gameState->setActiveDelayButton(true);
			body.setFillColor(sf::Color::Blue);
			switch (type) {
			case RESUME:
				gameState->setGameState(GAME);
				break;
			case EXIT:
				gameState->setGameState(END_GAME);
				break;
			case END_GAME_CONTINUE:
				gameState->setGameState(GAME);
				break;
			}
		}
		else
			body.setFillColor(sf::Color::Red);
	}
	else {
		body.setFillColor(sf::Color::White);
	}
}

void Button::Draw(sf::RenderWindow& window)
{
	window.draw(body);
	window.draw(text);
}
