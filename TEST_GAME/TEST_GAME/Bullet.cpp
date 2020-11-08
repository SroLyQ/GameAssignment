#include "bullet.h"

Bullet::Bullet(sf::Texture* texture, int type, bool faceRight, sf::Vector2f position)
{
	this->isDestroyBool = false;
	this->type = type;
	switch (type) {
	case 0:
		this->speed = 400.0f;
		this->faceRight = faceRight;
		this->damage = 50.0f;
		break;
	case 1:
		this->speed = 450.0f;
		this->faceRight = faceRight;
		this->damage = 20.0f;
		break;
	case 2:
		this->speed = 500.0f;
		this->faceRight = faceRight;
		this->damage = 150.0f;
		break;
	}
	body.setSize(sf::Vector2f(8.0f, 8.0f));
	body.setOrigin(body.getSize() / 2.0f);
	if (faceRight)
		body.setPosition(position.x+10.0f,position.y);
	else
		body.setPosition(position.x - 10.0f, position.y);
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

void Bullet::setDestroy(bool isDestroy)
{
	this->isDestroyBool = isDestroy;
}

