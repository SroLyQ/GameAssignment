#include "bullet.h"

Bullet::Bullet(sf::Texture* texture, int type, bool faceRight, sf::Vector2f position)
{
	this->isDestroyBool = false;
	this->type = type;
	this->isFadingBool = false;
	this->fadingTime = 0.0f;
	fadingClock.restart();
	switch (type) {
	case 0:
		this->speed = 400.0f;
		this->faceRight = faceRight;
		this->damage = 75.0f;
		body.setSize(sf::Vector2f(8.0f, 8.0f));
		if (faceRight)
			body.setPosition(position.x + 10.0f, position.y);
		else
			body.setPosition(position.x - 10.0f, position.y);
		break;
	case 1:
		this->speed = 450.0f;
		this->faceRight = faceRight;
		this->damage = 25.0f;
		body.setSize(sf::Vector2f(8.0f, 8.0f));
		body.setOrigin(body.getSize() / 2.0f);
		if (faceRight)
			body.setPosition(position.x + 10.0f, position.y);
		else
			body.setPosition(position.x - 10.0f, position.y);
		break;
	case 2:
		this->speed = 500.0f;
		this->faceRight = faceRight;
		this->damage = 225.0f;
		body.setSize(sf::Vector2f(8.0f, 8.0f));
		body.setOrigin(body.getSize() / 2.0f);
		if (faceRight)
			body.setPosition(position.x + 10.0f, position.y);
		else
			body.setPosition(position.x - 10.0f, position.y);
		break;
	case 3:
		this->speed = 0.0f;
		this->faceRight = faceRight;
		this->damage = 1000.0f;
		body.setSize(sf::Vector2f(300.0f, 10.0f));
		body.setOrigin(body.getSize() / 2.0f);
		if (faceRight)
			body.setPosition(position.x + 160.0f, position.y);
		else
			body.setPosition(position.x - 160.0f, position.y);
		break;
	}
	body.setOutlineColor(sf::Color::Red);
	body.setOutlineThickness(1);
	body.setTexture(texture);
}

Bullet::~Bullet()
{
}

void Bullet::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}

void Bullet::Update(float deltaTime)
{
	
	if (this->type != 3) {

		velocity.x *= 0.0f;
		if (faceRight) {
			velocity.x += speed;
		}
		else if (!faceRight) {
			velocity.x -= speed;
		}
		if (body.getPosition().x > 1080 || body.getPosition().x < 0) {
			isDestroyBool = true;
		}
		body.move(velocity*deltaTime);
	}
	if (this->type == 3) {
		fadingTime = fadingClock.getElapsedTime().asMilliseconds();
	}
}

void Bullet::setDestroy(bool isDestroy)
{
	this->isDestroyBool = isDestroy;
}

