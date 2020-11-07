#include "Gun.h"

Gun::Gun(int type,Collider col, std::vector<sf::Texture*> vectTexture)
{
	this->isPickUpBool = false;
	this->type = type;

	switch (type) {
		case 0:
			body.setTexture(vectTexture[0]);
			body.setSize(sf::Vector2f(20.0f, 10.0f));
			body.setOrigin(body.getSize() / 2.0f);
			body.setPosition(col.GetPosition());
			break;
		case 1:
			body.setTexture(vectTexture[1]);
			body.setSize(sf::Vector2f( 30.0f,16.0f));
			body.setOrigin(body.getSize() / 2.0f);
			body.setPosition(col.GetPosition());
			break;
		case 2:
			body.setTexture(vectTexture[2]);
			body.setSize(sf::Vector2f(24.0f, 12.0f));
			body.setOrigin(body.getSize() / 2.0f);
			body.setPosition(col.GetPosition());
			break;
	}
}

void Gun::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}

void Gun::setPickUp(bool isPickUp)
{
	this->isPickUpBool = isPickUp;
}
