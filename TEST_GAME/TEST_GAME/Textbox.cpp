#include "Textbox.h"

Textbox::Textbox(int size, sf::Color color, bool sel, sf::Font& font, sf::Vector2f position)
{
	textbox.setCharacterSize(size);
	textbox.setFont(font);
	textbox.setPosition(position);
	this->hasLimit = true;
	this->limit = 11;
	isSelectedBool = sel;
	if (sel) {
		textbox.setString("|");
	}
	else {
		textbox.setString("");
	}
	textbox.setFillColor(color);
	body.setSize(sf::Vector2f(260.0f, 50.0f));
	body.setFillColor(sf::Color(155, 155, 155, 70));
	body.setPosition(position.x - 15.0f, position.y - 15.0f);
}

void Textbox::setSelected(bool sel)
{
	isSelectedBool = sel;
	if (!sel) {
		std::string t = text.str();
		std::string newT = "";
		for (int i = 0;i < t.length() - 1;i++) {
			newT += t[i];
		}
		textbox.setString(newT);
	}
}

void Textbox::Draw(sf::RenderWindow& window)
{
	window.draw(body);
	window.draw(textbox);
}

void Textbox::typedOn(sf::Event input)
{
	if (isSelectedBool) {
		int charTyped = input.text.unicode;
		if (charTyped < 128) {
			if (hasLimit) {
				if (text.str().length() <= limit) {
					inputLogic(charTyped);
				}
				else if (text.str().length() > limit && charTyped == DELETE_KEY) {
					deleteLastChar();
				}
			}
		}
	}
}

void Textbox::Update(State* state, sf::Vector2i mousePos)
{
	if (isSelectedBool) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) || state->getGameState() == GAME) {
			name = text.str();
			isSelectedBool = false;
		}
	}
	if (state->getGameState() == MENU) {
		if (body.getGlobalBounds().contains(sf::Vector2f(mousePos))) {
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !state->isActiveDelayButton()) {
				state->setActiveDelayButton(true);
				this->isSelectedBool = !this->isSelectedBool;
				if (isSelectedBool) {
					textbox.setString("|");
				}
				else {
					textbox.setString("");
				}
			}
		}
		else {
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !state->isActiveDelayButton()) {
				state->setActiveDelayButton(true);
				this->isSelectedBool = false;
			}
		}

	}
}

void Textbox::resetString()
{
	textbox.setString("");
	text.str("");
}

void Textbox::inputLogic(int charTyped)
{
	if (charTyped != DELETE_KEY && charTyped != ENTER_KEY && charTyped != ESCAPE_KEY) {
		text << static_cast<char>(charTyped);
	}
	else if (charTyped == DELETE_KEY) {
		if (text.str().length() > 0) {
			deleteLastChar();
		}
	}
	textbox.setString(text.str() + "|");
}

void Textbox::deleteLastChar()
{
	std::string t = text.str();
	std::string newT = "";
	for (int i = 0;i < t.length() - 1;i++) {
		newT += t[i];
	}
	text.str("");
	text << newT;

	textbox.setString(text.str());
}
