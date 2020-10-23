#include "bullet.h"

Bullet::Bullet(sf::Texture *texture,int type, bool faceRight,sf::Vector2f position)
{
	if (type == 1) {
		this->speed = 400.0f;
		this->faceRight = faceRight;
		isDestroyBool = false;
		this->damage = 50.0f;
		body.setSize(sf::Vector2f(10.0f, 10.0f));
		body.setOrigin(body.getSize() / 2.0f);
		body.setPosition(position);
		body.setTexture(texture);
	}
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

