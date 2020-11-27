#pragma once
#include "Initial.h"

#define DELETE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27

class Textbox
{
public:
	Textbox(int size,sf::Color color, bool sel,sf::Font &font,sf::Vector2f position);

	void setSelected(bool sel);
	void Draw(sf::RenderWindow& window);
	void typedOn(sf::Event input);
	void Update(State* state, sf::Vector2i mousePos);
	void resetString();

	std::string getText() { return text.str(); }
	std::string getName() { return name; }

private:
	sf::Text textbox;
	sf::RectangleShape body;
	std::string name;
	std::ostringstream text;

	bool isSelectedBool;
	bool hasLimit;
	int limit;

	void inputLogic(int charTyped);
	void deleteLastChar();
};

