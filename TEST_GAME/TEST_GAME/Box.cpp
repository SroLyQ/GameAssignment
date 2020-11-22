#include "Box.h"

Box::Box(sf::Texture* texture, sf::Vector2f position,int gunType)
{
	this->hp = 50;
	this->gunType = gunType;
	this->isDestroyBool = false;
	this->isOnGroundBool = false;
	body.setSize(sf::Vector2f(35.0f, 35.0f));
	body.setOrigin(body.getSize()/2.0f);
	body.setPosition(position);
	body.setTexture(texture);
	switch (gunType%7) {
	case 0: case 1: case 4:
			this->gunType = 1;
			break;
	case 5:	case 2: case 6:
			this->gunType = 2;
			break;
		case 3: 
			this->gunType = 3;
			break;
	}
}

Box::~Box()
{
}

void Box::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}

void Box::Update(float deltaTime)
{
	velocity.y = 981.0f * deltaTime;
	if (this->hp <= 0) {
		this->isDestroyBool = true;
	}
	body.move(velocity);
}

void Box::OnCollision(sf::Vector2f direction)
{
	if (direction.x < 0.0f) {
		velocity.x = 0.0f;
	}
	else if (direction.x > 0.0f) {
		velocity.x = 0.0f;
	}
	if (direction.y < 0.0f) {
		velocity.y = 0.0f;
	}
}

void Box::hitWithBullet(Bullet& bullet)
{
	this->hp -= bullet.GetDamage();
	
}

void Box::setIsOnGround(bool isOnGround)
{
	this->isOnGroundBool = isOnGround;
}
