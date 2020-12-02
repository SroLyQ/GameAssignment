#include "Button.h"

Button::Button(sf::Vector2f position, sf::Vector2f size, sf::Font* font, std::string text, sf::Texture* texture, int state, int type, sf::SoundBuffer* buttonHitBuffer)
{
	body.setSize(size);
	body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(position);
	body.setTexture(texture);
	this->state = state;
	this->type = type;
	this->font = font;
	this->text.setFont(*this->font);
	buttonHitSF.setBuffer(*buttonHitBuffer);
	buttonHitSF.setVolume(100);
	
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
	case MENU_START:
		this->text.setPosition(sf::Vector2f(position.x-80.0f, position.y-11.0f));
		this->text.setFillColor(sf::Color::White);
		this->text.setCharacterSize(32);
		break;
	case MENU_HIGHSCORE:
		this->text.setPosition(sf::Vector2f(position.x - 115.0f, position.y - 11.0f));
		this->text.setFillColor(sf::Color::White);
		this->text.setCharacterSize(26);
		break;
	case MENU_HIGHSCORE_EXIT:
		this->text.setPosition(sf::Vector2f(position.x - 60.0f, position.y - 11.0f));
		this->text.setFillColor(sf::Color::Red);
		this->text.setCharacterSize(24);
		break;
	case MENU_HOWTOPLAY:
		this->text.setPosition(sf::Vector2f(position.x - 70.0f, position.y - 11.0f));
		this->text.setFillColor(sf::Color::White);
		this->text.setCharacterSize(18);
		break;
	case MENU_HOWTOPLAY_EXIT:
		this->text.setPosition(sf::Vector2f(position.x - 68.0f, position.y - 11.0f));
		this->text.setFillColor(sf::Color::Red);
		this->text.setCharacterSize(28);
		break;

	case MENU_EXIT:
		this->text.setPosition(sf::Vector2f(position.x - 40.0f, position.y - 11.0f));
		this->text.setFillColor(sf::Color::Red);
		this->text.setCharacterSize(20);
		break;
	}
	this->text.setOutlineColor(sf::Color::Black);
	this->text.setOutlineThickness(2);
	this->text.setString(text);
}

void Button::Update(sf::Vector2i mousePos, State* gameState)
{
	if (this->body.getGlobalBounds().contains(sf::Vector2f(mousePos))) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !gameState->isActiveDelayButton()) {
			buttonHitSF.play();
			gameState->setActiveDelayButton(true);
			body.setFillColor(sf::Color(133.0f, 87.0f, 35.0f));
			switch (type) {
			case RESUME:
				gameState->setGameState(GAME);
				break;
			case EXIT:
				gameState->setGameState(END_GAME);
				break;
			case END_GAME_CONTINUE:
				gameState->setGameState(MENU);
				break;
			case MENU_START:
				gameState->setGameState(GAME);
				gameState->setShowHighScore(false);
				gameState->setPushButton(false);
				break;
			case MENU_HIGHSCORE:
				gameState->setGameState(MENU);
				gameState->setShowHighScore(true);
				break;
			case MENU_HIGHSCORE_EXIT:
				gameState->setGameState(MENU);
				gameState->setShowHighScore(false);
				gameState->setPushButton(false);
				break;
			case MENU_HOWTOPLAY:
				gameState->setShowHighScore(false);
				gameState->setPushButton(false);
				gameState->setShowHowToPlay(true);
				break;
			case MENU_HOWTOPLAY_EXIT:
				gameState->setGameState(MENU);
				gameState->setShowHowToPlay(false);
				gameState->setPushButton(false);

				break;
			case MENU_EXIT:
				gameState->setCloseGame(true);
				break;
			}
		}
		else {
			body.setFillColor(sf::Color::White);
			body.setOutlineColor(sf::Color::White);
			body.setOutlineThickness(2);

		}
	}
	else {
		switch (type) {
		case MENU_START:
			this->text.setFillColor(sf::Color::White);
			break;
		}
		body.setFillColor(sf::Color::White);
		body.setOutlineThickness(0);
	}
}

void Button::Draw(sf::RenderWindow& window)
{
	window.draw(body);
	window.draw(text);
}
