#include "Button.h"

Button::Button(sf::Vector2f position, sf::Vector2f size, sf::Font* font, std::string text, sf::Texture* texture)
{
	body.setSize(size);
	body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(position);

	this->font = font;
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setCharacterSize(24);
}

void Button::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}
