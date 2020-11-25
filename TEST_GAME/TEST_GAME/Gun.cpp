#include "Gun.h"

Gun::Gun(int type, Collider col, std::vector<sf::Texture*> vectTexture)
{
	this->isPickUpBool = false;
	this->type = type;
	this->moveUp = false; 
	this->speed = 4.0f;
	this->isDestroyBool = false;
	this->pauseTime = 0.0f;
	switch (type) {
	case 1:
		body.setTexture(vectTexture[1]);
		body.setSize(sf::Vector2f(30.0f, 16.0f));
		body.setOrigin(body.getSize() / 2.0f);
		body.setPosition(col.GetPosition());
		break;
	case 2:
		body.setTexture(vectTexture[2]);
		body.setSize(sf::Vector2f(24.0f, 12.0f));
		body.setOrigin(body.getSize() / 2.0f);
		body.setPosition(col.GetPosition());
		break;
	case 3:
		body.setTexture(vectTexture[3]);
		body.setSize(sf::Vector2f(34.0f, 16.0f));
		body.setOrigin(body.getSize() / 2.0f);
		body.setPosition(col.GetPosition());
	}
	this->startPosition = body.getPosition();
}
void Gun::Update(float deltaTime, State* state)
{
	this->timeAlive = clockAlive.getElapsedTime().asSeconds();
	if (this->timeAlive - pauseTime > 10.0f) {
		body.setFillColor(sf::Color(255, 255, 255, 255));
		isDestroyBool = true;
	}
	else if (this->timeAlive - pauseTime > 9.5f) {
		body.setFillColor(sf::Color(255, 255, 255, 128));

	}
	else if (this->timeAlive - pauseTime > 9.0f) {
		body.setFillColor(sf::Color(255, 255, 255, 255));

	}
	else if (this->timeAlive - pauseTime > 8.5f) {
		body.setFillColor(sf::Color(255, 255, 255, 128));

	}
	else if (this->timeAlive - pauseTime > 8.0f) {
		body.setFillColor(sf::Color(255, 255, 255, 255));

	}
	else if (this->timeAlive - pauseTime > 7.5f) {
		body.setFillColor(sf::Color(255, 255, 255, 128));

	}
	if (body.getPosition().y < this->startPosition.y - 8.0f && moveUp) {
		moveUp = false;
	}
	if (body.getPosition().y > this->startPosition.y + 8.0f && !moveUp) {
		moveUp = true;
	}
	if (moveUp) {
		body.move(0, -speed * deltaTime);
	}
	else {
		body.move(0, speed * deltaTime);
	}


}
void Gun::setPauseTime(float pauseTime)
{
	this->pauseTime += pauseTime;
}
void Gun::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}

void Gun::setPickUp(bool isPickUp)
{
	this->isPickUpBool = isPickUp;
}
