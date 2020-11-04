#include "Box.h"

Box::Box(sf::Texture* texture, sf::Vector2f position)
{
	srand(time(NULL));
	this->hp = 50;
	this->isDestroyBool = false;
	body.setSize(sf::Vector2f(35.0f, 35.0f));
	body.setOrigin(body.getSize()/2.0f);
	body.setPosition(position);
	body.setTexture(texture);
	int ran = rand();
	switch (ran%3) {
		case 0: 
			this->gunType = 0;
			break;
		case 1:
			this->gunType = 1;
			break;
		case 2:
			this->gunType = 2;
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
	srand(time(NULL));
	velocity.y = 981.0f * deltaTime;
	if (this->hp <= 0) {
		int temp = rand();
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
